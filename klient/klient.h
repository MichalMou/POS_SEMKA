#ifndef UNTITLED6_KLIENT_H
#define UNTITLED6_KLIENT_H

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

using namespace std;

class Klient {
public:
    Klient(char *ipadressa, int port);
    ~Klient();
    // TODO read a wri
    void pridajServer(int server) ;
    void posliSpravu(char* sprava);

    int getSocketFD() const;
    bool getKoniec() const;

private:
    int socketfd;
    int server;
    bool koniec;
};


#endif //UNTITLED6_KLIENT_H
