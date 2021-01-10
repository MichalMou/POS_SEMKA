#include "klient.h"

using namespace std;

#include <iostream>
#include <string.h>
#include <pthread.h>


#define BUFF_N 1024

void *primiSpravu(void *parameter) {
    Klient *klient = reinterpret_cast<Klient *>(parameter);
    char buffer[BUFF_N];
    do {
        bzero(buffer, BUFF_N);
        //cout << "idem cakat na read" << endl;

        int n = read(klient->getSocketFD(), buffer, BUFF_N - 1);
        //cout << "necakam na read" << endl;
        pthread_mutex_lock(klient->getMutex());
        //cout << "necakam na mutex" << endl;

        if (n > 0) {
            string sprava = buffer;
            klient->zapisOdpoved(sprava);
            //cout << "primac, sprava zapisana " << klient->getZoznamSprav().size() << endl;
            n = 0;
        }
        pthread_mutex_unlock(klient->getMutex());

        n = 0;
        //cout << "opakujem podmienku zle je" << endl;

    } while (!klient->getKoniec());
}

Klient::Klient(const string &ipadressa, int port) {
    pthread_mutex_init(&mutex_odpovede, NULL);
    poslednaSprava = 0;
    koniec = false;
    struct sockaddr_in servAddr;
    struct hostent *server;
    char buffer[BUFF_N];
    server = gethostbyname(ipadressa.c_str());

    if (server == NULL) {
        perror("Taky server nepoznam!\n");
    }
    bzero((char *) &servAddr, sizeof(servAddr));

    servAddr.sin_family = AF_INET;
    bcopy((char *) server->h_addr,
          (char *) &servAddr.sin_addr.s_addr,
          server->h_length);
    servAddr.sin_port = htons(port);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0) {
        perror("Nedokazalo sa vytvorit!\n");
    }

    if (connect(socketfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
        cout << "Nedokazalo sa pripojit!" << endl;
    } else {
        cout << "pripojil sa na server" << endl;
    }

    pthread_create(&sprava, NULL, &primiSpravu, this);
}

Klient::~Klient() {
    shutdown(getSocketFD(), SHUT_RDWR);
    close(getSocketFD());

    pthread_join(getSprava(), NULL);
    pthread_mutex_destroy(&mutex_odpovede);
}

// posle spravu serveru
void Klient::posliSpravu(string odosielanaSprava) {
    int size = odosielanaSprava.size();
    int n = write(this->getSocketFD(), odosielanaSprava.c_str(), size);
}

//  prejst cely zoznamSprav najst response na spravu
string Klient::precitaj(string query) {

    pthread_mutex_lock(getMutex());
    while (poslednaSprava >= zoznamSprav.size()) {
        pthread_mutex_unlock(getMutex());
        pthread_mutex_lock(getMutex());
    }
    pthread_mutex_unlock(getMutex());

    string vratit;
    pthread_mutex_lock(getMutex());
    for (string zaznam : zoznamSprav) {
        if (zaznam.find(query) != string::npos) {
            vratit = zaznam;
            zoznamSprav.pop_back();
            pthread_mutex_unlock(getMutex());
            return vratit;
        }
    }
    pthread_mutex_unlock(getMutex());

    return "Error odpoved na query sa nenasla!";

}

vector<string> Klient::getZoznamSprav() {
    return this->zoznamSprav;
}

bool Klient::getKoniec() const {
    return this->koniec;
}

int Klient::getSocketFD() const {
    return this->socketfd;
}

pthread_t Klient::getSprava() {
    return this->sprava;
}

pthread_mutex_t *Klient::getMutex() {
    return &this->mutex_odpovede;
}

void Klient::zapisOdpoved(string odpoved) {
    zoznamSprav.push_back(odpoved);
}

void Klient::ukonci() {
    this->koniec = true;
}

#undef BUFF_N
