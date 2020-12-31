#include "klient.h"

using namespace std;

#include <iostream>
#include <string.h>

#define BUFF_N 1024

void* primiSpravu(void* parameter) {
    Klient *klient = reinterpret_cast<Klient *>(parameter);
    char buffer[BUFF_N];
    do {
            bzero(buffer, BUFF_N);
            int n = read(klient->getSocketFD(), buffer, BUFF_N - 1);
            if (n > 0){
                cout << "mam spravu: " << buffer << endl;
                klient->getZoznamSprav().push_back(buffer);
                // ak bude problem s dlzkou spravy tak dorobit rozkuskovanie
            }
    }
    while (!klient->getKoniec());
}

Klient::Klient(const string& ipadressa, int port) {
    koniec = false;
    struct sockaddr_in servAddr;
    struct hostent* server;
    char buffer[BUFF_N];

    server = gethostbyname(ipadressa.c_str());

    if(server == NULL){
        cout << "Taky server nepoznam!" << endl;
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
        cout << "Nedokazalo sa vytvorit!" << endl;
    }

    if(connect(socketfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        cout << "Nedokazalo sa pripojit!" << endl;
    }

    pthread_create(&sprava, NULL, &primiSpravu, this);
}

Klient::~Klient() {
    close(getSocketFD());
    pthread_join(getSprava(), NULL);
}

void Klient::posliSpravu(char *odosielanaSprava) const {
    write(this->getSocketFD(), odosielanaSprava, strlen(odosielanaSprava) + 1);
}

//  prejst cely zoznamSprav najst response na spravu
string Klient::precitaj(char *query) {
    read(this->getSocketFD(), query, strlen(query) + 1);
    for (string zaznam : zoznamSprav) {

        if(zaznam.find(query) != std::string::npos){
            return zaznam;
        }
    }
}

vector<string> Klient::getZoznamSprav() {
    return this->zoznamSprav;
}

bool Klient::getKoniec() const {
    return this->koniec;
}

int Klient::getSocketFD() const {
    return this->socketfd;
}

pthread_t Klient::getSprava() {
    return this->sprava;
}

#undef BUFF_N

/*
 * posles: query getNick 123456
 * dostanes: response getNick 123456 response Ferko
 *
 *
 * // TODO dorobit rozdelenie sprav ked su priliz velke
 */