#include <stdio.h>      
#include <sys/types.h>
#include <sys/socket.h>   
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {

    int simpleSocket = 0;
    int simplePort = 0;
    int returnStatus = 0;
    char buffer[256] = "";
    struct sockaddr_in simpleServer;

    if (3 != argc) {
        fprintf(stderr, "Usage: %s <server> <port>\n", argv[0]);
        exit(1);
    }

    /* ask the user for their name */
    char name[256];
    printf("Inserisci il tuo nome: ");
    fflush(stdout);
    if (!fgets(name, sizeof(name), stdin)) {
        fprintf(stderr, "Invalid input\n");
        exit(1);
    }
    /* remove newline */
    char *nl = strchr(name, '\n');
    if (nl) *nl = '\0';
    if (name[0] == '\0') {
        fprintf(stderr, "Empty name, exiting\n");
        exit(1);
    }

    /* create a streaming socket      */
    simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (simpleSocket == -1) {
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    }
    else {
        fprintf(stderr, "Socket created!\n");
    }

    /* retrieve the port number for connecting */
    simplePort = atoi(argv[2]);

    /* setup the address structure */
    memset(&simpleServer, '\0', sizeof(simpleServer));
    simpleServer.sin_family = AF_INET;
    simpleServer.sin_addr.s_addr=inet_addr(argv[1]);
    simpleServer.sin_port = htons(simplePort);

    /*  connect to the address and port with our socket  */
    returnStatus = connect(simpleSocket, (struct sockaddr *)&simpleServer, sizeof(simpleServer));

    if (returnStatus == 0) {
        fprintf(stderr, "Connect successful!\n");
    }
    else {
        fprintf(stderr, "Could not connect to address!\n");
    close(simpleSocket);
    exit(1);
    }

    /* SEND THE NAME TO THE SERVER (append newline) */
    char sendbuf[300];
    snprintf(sendbuf, sizeof(sendbuf), "%s\n", name);
    if (write(simpleSocket, sendbuf, strlen(sendbuf)) < 0) {
        perror("write");
        close(simpleSocket);
        exit(1);
    }

    /* read the server response */
    ssize_t nread;
    char rbuf[512];
    while ((nread = read(simpleSocket, rbuf, sizeof(rbuf)-1)) > 0) {
        rbuf[nread] = '\0';
        printf("%s", rbuf);
    }
    if (nread < 0) {
        perror("read");
    }

    close(simpleSocket);
    return 0;
}
