#ifndef UNTITLED6_KLIENT_H
#define UNTITLED6_KLIENT_H

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <strings.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

using namespace std;

class Klient {
public:
    Klient(string ipadressa, int port);
    ~Klient();
    // TODO read a wri
    void posliSpravu(char* sprava);
    string precitaj(char* sprava);
    int getSocketFD() const;
    bool getKoniec() const;

private:
    int socketfd;
    bool koniec;
};


#endif //UNTITLED6_KLIENT_H
