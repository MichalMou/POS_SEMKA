#ifndef UNTITLED6_KLIENT_H
#define UNTITLED6_KLIENT_H

#include <stdio.h>
#include <vector>
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
    Klient(const string& ipadressa, int port);
    ~Klient();
    void posliSpravu(char* sprava);
    string precitaj(string query);

    pthread_t getSprava();
    int getSocketFD() const;
    bool getKoniec() const;
    vector<string> getZoznamSprav();

private:
    vector<string> zoznamSprav;
    pthread_t sprava;
    int socketfd;
    bool koniec;
};


#endif //UNTITLED6_KLIENT_H
