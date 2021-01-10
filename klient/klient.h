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
    void posliSpravu(string sprava);
    string precitaj(string query);
    void zapisOdpoved(string odpoved);
    void ukonci();

    pthread_t getSprava();
    int getSocketFD() const;
    bool getKoniec() const;
    vector<string> getZoznamSprav();
    pthread_mutex_t * getMutex();

private:
    vector<string> zoznamSprav;
    pthread_t sprava;
    pthread_mutex_t mutex_odpovede;
    int socketfd;
    bool koniec;
    int poslednaSprava;
};


#endif //UNTITLED6_KLIENT_H
