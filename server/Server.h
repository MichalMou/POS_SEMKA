#ifndef UNTITLED6_SERVER_H
#define UNTITLED6_SERVER_H

#include <cstring>
#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <vector>

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
    vector<string>* getZoznamSprav();

private:
    pthread_t klienti_t[20];
    //pthread_t sprava;
    pthread_t primac_spojeni;
    int socketfd;
    vector<int>* klienti;
    bool koniec;
    };

#endif //UNTITLED6_SERVER_H
