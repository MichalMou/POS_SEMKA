#include "klient.h"

using namespace std;


void* connectSpojenie(void* parameter) {
    Klient* klient  = reinterpret_cast<Klient*>(parameter);

    struct sockaddr_in serAddr;
    socklen_t serLength = sizeof(serAddr);
    while(!klient->getKoniec()) {
        int newSocketfd = accept(klient->getSocketFD(), (struct sockaddr*)&serAddr, &serLength);
        if (newSocketfd > 0) {
            klient->pridajServer();
        }
    }
}


void* primacSprav(void* parameter) {
    Server *server = reinterpret_cast<Server *>(parameter);
    char buffer[256];

    do {
        for(int newSock : *server->getKlienti()){
            bzero(buffer, 256);
            int n = read(newSock, buffer, 255);
            if (n > 0){
                cout << "mam spravu: " << buffer << endl;
            }
        }
    }
    while (!server->getKoniec());
}

Klient::Klient(char *ipadressa, int port) {

    int socketfd, n;
    struct sockaddr_in servAddr;
    struct hostent* server;
    char buffer[256];

    server = gethostbyname(argv[1]);
    if(server == NULL){
        fprintf(stderr, "Taky server nepoznam!");
        return 2;
    }

    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    bcopy(
            (char*)server->h_addr,
            (char*)&servAddr.sin_addr.s_addr,
            server->h_length
    );
    servAddr.sin_port = htons(atoi(argv[2]));

    socketfd = socket(AF_INET,SOCK_STREAM, 0);
    if(socketfd < 0){
        perror("Nedokazalo sa vytvorit!");
        return 3;
    }

    if(connect(socketfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        perror("Nedokazalo sa pripojit!");
        return 4;
    }

    for(int i = 0; i < 5; i++){
        printf( "Prosim zadajte %d spravu pre server:", i+1);
        bzero(buffer, 256);
        fgets(buffer, 255, stdin);
    }

    n = write(socketfd, buffer, strlen(buffer));
    if(n < 0) {
        perror("Nepodarilo sa ulozit informaciu do socketu!");
        return 5;
    }

    bzero(buffer, 256);
    n = read(socketfd, buffer, 256);
    if(n < 0) {
        perror("Neprecital som spravu!");
        return 6;
    }

    printf("%s\n", buffer);
}

Klient::~Klient() {

}

void Klient::pridajServer(int server) {

}

void Klient::posliSpravu(char *sprava) {

}

