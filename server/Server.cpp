//
// Created by Michal on 29. 12. 2020.
//

#include "Server.h"

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
using namespace std;

void* connectSpojenie(void* parameter) {
    Server* server  = reinterpret_cast<Server*>(parameter);

    while(true) { // TODO podmienka zastavit server
        int newSocketfd = accept(server->getSocketFD,(struct sockaddr * ) &cliAddr, &clientLength);
        if (newSocketfd > 0) {
            server->pridajClienta();
        }
    }
}

void* primacSprav(void* parameter) {
    Server *server = reinterpret_cast<Server *>(parameter);
    do {
        // TODO foreach clienti, ak n je vacsie mam spravu
        bzero(buffer, BUFF_N);
        n = read(newSocketfd, buffer, BUFF_N - 1);
    }
    while (true); // TODO kim sa nezastavi server
}

int Server::getSocketFD(){
    return socketFd;
    //
}

void Server::pridajClienta(int client) {
    // pridat do zoznamu cli (vector napr)
}

void Server::posliSpravu(int client) {
    const char * msg = "Dostal som tvoju spravu %s\n";
    n = write(newSocketfd,msg,strlen(msg) + 1);

}


int Server::Server(int port) { // TODO urobit z tohoto konstruktor
#define BUFF_N 256
    // atributy


    int socketfd, newSocketfd;
    socklen_t clientLength;
    struct sockaddr_in cliAddr, servAddr;
    int n;
    char buffer[BUFF_N];

    bzero((char*)&servAddr,sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(port);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd < 0){
        perror("Chyba pri vytvarani socketu :");
        return 1;
    }

    if(bind(socketfd,(struct sockaddr*) &servAddr, sizeof(servAddr)) < 0){
        perror("Chyba pri bindovani socketu :");
        return 2;
    }
    listen(socketfd, 5);
    clientLength = sizeof(cliAddr);

    // TODO spustit thready

#undef BUFF_N
    close(socketfd);
    close(newSocketfd);
    return 0;
}
