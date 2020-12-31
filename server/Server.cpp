#include "Server.h"


using namespace std;

#define BUFF_N 1024

void* connectSpojenie(void* parameter) {
    Server* server  = reinterpret_cast<Server*>(parameter);

    struct sockaddr_in kliAddr;
    socklen_t klientLength = sizeof(kliAddr);
    while(!server->getKoniec()) {
        int newSocketfd = accept(server->getSocketFD(), (struct sockaddr*)&kliAddr, &klientLength);
        if (newSocketfd > 0) {
            server->pridajKlienta(newSocketfd);
        }
    }
}


void* primacSprav(void* parameter) {
    Server *server = reinterpret_cast<Server *>(parameter);
    char buffer[BUFF_N];

    do {
        for(int newSock : *server->getKlienti()){
            bzero(buffer, BUFF_N);
            int n = read(newSock, buffer, BUFF_N - 1);
            if (n > 0){
                cout << "mam spravu: " << buffer << endl;
            }
        }
    }
    while (!server->getKoniec());
}

Server::Server(int port) {

    koniec = false;
    struct sockaddr_in servAddr;
    bzero((char*)&servAddr,sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(port);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(bind(socketfd,(struct sockaddr*) &servAddr, sizeof(servAddr)) < 0){
        perror("Chyba pri bindovani socketu :");
    }
    listen(socketfd, 5);

    pthread_create(&sprava, NULL, &primacSprav, this);
}

Server::~Server() {
    for (int klient : *getKlienti()) {
        close(klient);
    }
    pthread_join(sprava,NULL);
    delete klienti;
    close(socketfd);
}

int Server::getSocketFD() const{
    return socketfd;
}

void Server::pridajKlienta(int klient) {
    klienti->push_back(klient);
}

void Server::posliSpravu(int klientSock, char * sprava) {
    int n = write(klientSock,sprava,strlen(sprava) + 1);
}

const vector<int> *Server::getKlienti() {
    return this->klienti;
}

bool Server::getKoniec() const {
    return this->koniec;
}

#undef BUFF_N