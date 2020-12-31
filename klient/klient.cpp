#include "klient.h"

using namespace std;

#include <iostream>
#include <string.h>

void* primiSpravu(void* parameter) {
    Klient *klient = reinterpret_cast<Klient *>(parameter);
    char buffer[256];
    do {
            bzero(buffer, 256);
            int n = read(klient->getSocketFD(), buffer, 255);
            if (n > 0){
                cout << "mam spravu: " << buffer << endl;
                // TODO uloz spravu/buffer do spravy

            }
    }
    while (!klient->getKoniec());
}


Klient::Klient(string ipadressa, int port) {
    struct sockaddr_in servAddr;
    struct hostent* server;
    char buffer[256];

    server = gethostbyname(ipadressa.c_str());
    if(server == NULL){
        fprintf(stderr, "Taky server nepoznam!");
        throw // TODO
    }

    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    bcopy(
            (char*)server->h_addr,
            (char*)&servAddr.sin_addr.s_addr,
            server->h_length
    );
    servAddr.sin_port = htons(port);

    socketfd = socket(AF_INET,SOCK_STREAM, 0);
    if(socketfd < 0){
        perror("Nedokazalo sa vytvorit!");
        // TODO throw
    }

    if(connect(socketfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        perror("Nedokazalo sa pripojit!");
        // TODO throw
    }

    pthread_t sprava;
    pthread_create(&sprava, NULL, &primiSpravu, this);
}

Klient::~Klient() {
 //TODO
}



void Klient::posliSpravu(char *sprava) {
    write(this->getSocketFD(), sprava, strlen(sprava) + 1);
}

string Klient::precitaj(char *sprava) { //TODO odpoved na sprava, resposne je string

    write(this->getSocketFD(), sprava, strlen(sprava) + 1);
    while () {
        // prehladat pole a najst spravnu response
        return response;
    }
}


/*
 * posles: getNick 123456
 * dostanes: response getNick Ferko
 *
 * // TODO pole odpovedi,
 *
 * // TODO dorobit rozdelenie sprav ked su priliz velke
 */