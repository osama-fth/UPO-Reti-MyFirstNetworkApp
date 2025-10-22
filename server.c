#include <stdio.h>      
#include <sys/types.h>
#include <sys/socket.h>   
#include <netinet/in.h>   
#include <arpa/inet.h>    
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

const char MESSAGE[] = "Hello UPO student!\n";

int main(int argc, char *argv[]) {

    int simpleSocket = 0;
    int simplePort = 0;
    int returnStatus = 0;
    struct sockaddr_in simpleServer;

    if (2 != argc) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (simpleSocket == -1) {
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    }
    else {
        fprintf(stderr, "Socket created!\n");
    }

    /* retrieve the port number for listening */
    simplePort = atoi(argv[1]);

    /* setup the address structure */
    memset(&simpleServer, 0, sizeof(simpleServer)); 
    simpleServer.sin_family = AF_INET;
    simpleServer.sin_addr.s_addr = htonl(INADDR_ANY);
    simpleServer.sin_port = htons(simplePort);

    /*  bind to the address and port with our socket  */
    returnStatus = bind(simpleSocket,(struct sockaddr *)&simpleServer,sizeof(simpleServer));

    if (returnStatus == 0) {
        fprintf(stderr, "Bind completed!\n");
    }
    else {
        fprintf(stderr, "Could not bind to address!\n");
        close(simpleSocket);
        exit(1);
    }

    /* lets listen on the socket for connections      */
    returnStatus = listen(simpleSocket, 5);

    if (returnStatus == -1) {
        fprintf(stderr, "Cannot listen on socket!\n");
        close(simpleSocket);
        exit(1);
    }

    while (1){
        struct sockaddr_in clientName = { 0 };
        int simpleChildSocket = 0;
        socklen_t clientNameLength = sizeof(clientName);

        /* wait here */
        simpleChildSocket = accept(simpleSocket,(struct sockaddr *)&clientName, &clientNameLength);

        if (simpleChildSocket == -1) {
            fprintf(stderr, "Cannot accept connections!\n");
            close(simpleSocket);
            exit(1);
        }

        /* READ THE NAME SENT BY THE CLIENT (up to newline or EOF) */
        char buf[512];
        ssize_t total = 0;
        ssize_t n;
        while (total < (ssize_t)sizeof(buf)-1) {
            n = read(simpleChildSocket, buf + total, sizeof(buf)-1 - total);
            if (n <= 0) break;
            total += n;
            if (memchr(buf, '\n', total)) break;
        }
        if (total <= 0) {
            close(simpleChildSocket);
            continue;
        }
        buf[total] = '\0';
        /* remove trailing CR/LF if present */
        char *nl = strchr(buf, '\n');
        if (nl) *nl = '\0';
        char *cr = strchr(buf, '\r');
        if (cr) *cr = '\0';

        /* print client name */
        char *clientIP = inet_ntoa(clientName.sin_addr);
        int clientPort = ntohs(clientName.sin_port);
        fprintf(stderr, "Connection from %s:%d - received name: \"%s\"\n",
                clientIP, clientPort, buf);

        /* send greeting to the client */
        char reply[600];
        snprintf(reply, sizeof(reply), "Ciao %s!\n", buf);
        write(simpleChildSocket, reply, strlen(reply));

        close(simpleChildSocket);
    }
    
    close(simpleSocket);
    return 0;
}

