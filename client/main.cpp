//
// Created by Michal on 30. 12. 2020.
//


#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#define BUFF_N 256

int main(int argc, char *argv[]){
    int socketfd, n;
    struct sockaddr_in servAddr;
    struct hostent* server;
    char buffer[BUFF_N];

    if(argc < 3){
        fprintf(stderr, "Pouzitie %s ipaddresa_servera porn \n, argv[0]");
        return 1;
    }

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
        bzero(buffer, BUFF_N);
        fgets(buffer, BUFF_N - 1, stdin);
    }

    n = write(socketfd, buffer, strlen(buffer));
    if(n < 0) {
        perror("Nepodarilo sa ulozit informaciu do socketu!");
        return 5;
    }

    bzero(buffer, BUFF_N);
    n = read(socketfd, buffer, BUFF_N);
    if(n < 0) {
        perror("Neprecital som spravu!");
        return 6;
    }

    printf("%s\n", buffer);

#undef BUFF_N
    return 0;
}