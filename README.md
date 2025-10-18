# 🔗 myFirstNetworkApp — Demo di rete in C

![Linguaggio: C](https://img.shields.io/badge/Linguaggio-C-00599C?logo=c&logoColor=white)
![Build: Makefile](https://img.shields.io/badge/build-Makefile-orange?logo=gnu&logoColor=white)
![Protocol: TCP](https://img.shields.io/badge/protocollo-TCP%20%2F%20Sockets-2ea44f)

Esempio minimale di programmazione di rete (sockets) in C:
- Server TCP: invia “Hello UPO student!” a ogni client che si connette.
- Client TCP: si connette, legge una singola risposta e la stampa.

## 📁 Struttura
- Server: [server.c](/Users/osamafoutih/Desktop/uni/2anno/reti/myFirstNetworkApp/server.c)
- Client: [client.c](/Users/osamafoutih/Desktop/uni/2anno/reti/myFirstNetworkApp/client.c)
- Makefile: [Makefile](/Users/osamafoutih/Desktop/uni/2anno/reti/myFirstNetworkApp/Makefile)

## 🛠️ Build
Usa il Makefile .
```sh
cd myFirstNetworkApp
gcc server.c  -o server 
gcc client.c  -o client
```

## ▶️ Esecuzione
Apri due terminali.

1) Avvia il server (porta 5000 di esempio):
```sh
./server 5000
```

2) Avvia il client (IP locale e stessa porta):
```sh
./client 127.0.0.1 5000
```

Output atteso del client (esempio):
```
20: Hello UPO student!
```

## ❓ Note
- Dimostrazione didattica di reti con socket in C (modello client/server TCP).
- Il server serve più connessioni in sequenza (blocking I/O).
- Il messaggio inviato dal server è definito in `server.c` come `MESSAGE`.
