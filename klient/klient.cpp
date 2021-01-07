#include "klient.h"

using namespace std;

#include <iostream>
#include <string.h>
#include <pthread.h>


#define BUFF_N 1024

void* primiSpravu(void* parameter) {
    Klient *klient = reinterpret_cast<Klient *>(parameter);
    char buffer[BUFF_N];
    do {
            bzero(buffer, BUFF_N);
            int n = read(klient->getSocketFD(), buffer, BUFF_N - 1);
            if (n > 0){
                //cout << "mam spravu: " << buffer << endl;
                string sprava = buffer;
                string str(sprava);
                klient->getZoznamSprav().push_back(str);
                n = 0;
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
        perror("Taky server nepoznam!\n");
    }
    bzero((char*)&servAddr, sizeof(servAddr));

    servAddr.sin_family = AF_INET;
    bcopy((char*)server->h_addr,
            (char*)&servAddr.sin_addr.s_addr,
            server->h_length);
    servAddr.sin_port = htons(port);

    socketfd = socket(AF_INET,SOCK_STREAM, 0);
    if(socketfd < 0){
        perror("Nedokazalo sa vytvorit!\n");
    }
    if(connect(socketfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        perror("Nedokazalo sa pripojit!\n");
    }

    pthread_create(&sprava, NULL, &primiSpravu, this);
}

Klient::~Klient() {
    close(getSocketFD());
    pthread_join(getSprava(), NULL);
}

// posle spravu serveru
void Klient::posliSpravu(char *odosielanaSprava) {
    write(this->getSocketFD(), odosielanaSprava, strlen(odosielanaSprava) + 1);
}

//  prejst cely zoznamSprav najst response na spravu
string Klient::precitaj(string query) {
    for (string zaznam : zoznamSprav) {
        if(zaznam.find(query) != string::npos){
            return zaznam;
        }
    }
    return "Error odpoved na query sa nenasla!";
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
