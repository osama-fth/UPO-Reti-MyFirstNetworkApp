# 🔗 myFirstNetworkApp — Dimostrazione minima di rete in C

![Language: C](https://img.shields.io/badge/Language-C-00599C?logo=c&logoColor=white)
![Protocol: TCP](https://img.shields.io/badge/protocol-TCP%20%2F%20Sockets-2ea44f)

Esempio minimale di programmazione di rete (socket) in C:
- Server TCP: accetta una connessione, legge il nome del client e risponde con un saluto.
- Client TCP: chiede all'utente il proprio nome, si connette al server, invia il nome e stampa la risposta del server.

## 📁 Struttura
- Server: `server.c`
- Client: `client.c`

## 🛠️ Compilazione
```sh
cd myFirstNetworkApp
gcc server.c -o server
gcc client.c -o client
```

## ▶️ Esecuzione
Aprire due terminali.

1) Avviare il server (es. porta 5000):
```sh
./server 5000
```

2) Avviare il client da un altro terminale:
```sh
./client 127.0.0.1 5000
```
Il client chiederà:
```
Inserisci il tuo nome:
```
Digitare un nome e premere Invio. Il server stamperà il nome ricevuto e il client visualizzerà il saluto del server.

Esempio output del server (stderr):
```
Connection from 127.0.0.1:XXXXX - received name: "Mario"
```

Esempio output del client:
```
Ciao Mario!
```
