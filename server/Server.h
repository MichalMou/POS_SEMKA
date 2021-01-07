#ifndef UNTITLED6_SERVER_H
#define UNTITLED6_SERVER_H

#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include <vector>
#include "PrekladacServer.h"

using namespace std;

class Server {
public:
    Server(int port);
    ~Server();
    void pridajKlienta(int klient);
    void posliSpravu(int klient, char* sprava);

    int getSocketFD() const;
    const vector<int>* getKlienti();
    bool getKoniec() const;
    vector<pthread_t>* getKlienti_t();
    pthread_mutex_t* getMutexPrekladac();
    PrekladacServer* getPrekladac();

private:
    PrekladacServer prekladac;
    pthread_mutex_t mutex_prekladac;
    pthread_t primac_spojeni;
    vector<pthread_t> klienti_t;
    vector<int>* klienti;
    int socketfd;
    bool koniec;
    };

#endif //UNTITLED6_SERVER_H
