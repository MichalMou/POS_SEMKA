#include "klient.h"

using namespace std;

#include <iostream>
#include <string.h>

void* primiSpravu(void* parameter) {
    Klient *klient = reinterpret_cast<Klient *>(parameter);
    // TODO zvysit buffer 1024
    char buffer[256];
    do {
            bzero(buffer, 256);
            int n = read(klient->getSocketFD(), buffer, 255);
            if (n > 0){
                cout << "mam spravu: " << buffer << endl;
                klient->getZoznamSprav().push_back(buffer);
                // TODO uloz spravu/buffer do spravy

            }
    }
    while (!klient->getKoniec());
}


Klient::Klient(const string& ipadressa, int port) {
    koniec = false;
    struct sockaddr_in servAddr;
    struct hostent* server;
    char buffer[256];

    server = gethostbyname(ipadressa.c_str());
    if(server == NULL){
        fprintf(stderr, "Taky server nepoznam!");
        // TODO throw
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

    // pthread_t sprava;
    pthread_create(&sprava, NULL, &primiSpravu, this);
}

Klient::~Klient() {
     close(getSocketFD());
     pthread_join(getSprava(), NULL);
}



void Klient::posliSpravu(char *odosielanaSprava) const {
    write(this->getSocketFD(), odosielanaSprava, strlen(odosielanaSprava) + 1);
}

string Klient::precitaj(char *sprava) { //TODO odpoved na sprava, resposne je string

    write(this->getSocketFD(), sprava, strlen(sprava) + 1);
    while () {
        // prehladat pole a najst spravnu response
        return response;
    }
}

vector<string> Klient::getZoznamSprav() {
    return this->zoznamSprav;
}

bool Klient::getKoniec() const {
    return this->koniec;
}

int Klient::getSocketFD() const {
    return this->socketfd
}

pthread_t Klient::getSprava() {
    return this->sprava;
}


/*
 * posles: getNick 123456
 * dostanes: response getNick Ferko
 *
 * // TODO pole odpovedi,
 *
 * // TODO dorobit rozdelenie sprav ked su priliz velke
 */