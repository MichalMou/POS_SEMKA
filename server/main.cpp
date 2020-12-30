//
// Created by Michal on 30. 12. 2020.
//
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;


int main(int argc, char *argv[])
{
#define BUFF_N 256
    int socketfd, newSocketfd;
    socklen_t clientLength;
    struct sockaddr_in cliAddr, servAddr;
    int n;
    char buffer[BUFF_N];

    // overenie ci bol zadany port do argumentov
    if(argc < 2){
        printf("Nieje zadany port, socket zlyhal!");
        return 1;
    }

    bzero((char*)&servAddr,sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(atoi(argv[1]));

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

    newSocketfd = accept(socketfd,(struct sockaddr * ) &cliAddr, &clientLength);
    if(newSocketfd < 0){
        perror("Chyba pri akceptacii socketu");
        return 3;
    }
    bzero(buffer, BUFF_N);
    n = read(newSocketfd, buffer, BUFF_N - 1);
    if(n < 0){
        perror("Chyba pri citani zo socketu");
        return 4;
    }
    printf("Dostal som spravu %s\n", buffer);

    const char * msg = "Dostal som tvoju spravu %s\n";
    n = write(newSocketfd,msg,strlen(msg) + 1);
    if(n < 0) {
        perror("Chyba pri zapise do socketu");
        return 4;
    }

#undef BUFF_N
    close(socketfd);
    close(newSocketfd);
    return 0;
}
