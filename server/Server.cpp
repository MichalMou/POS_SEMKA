#include <search.h>
#include "Server.h"

using namespace std;

#define BUFF_N 1024

struct zak {
    Server* server;
    int socket;
};

/*
 * robi iba s vlaknom ktore mu bolo dane preto mame vlakno+primacSprav pre kazdy socket
 */
void* primacSprav(void* parameter) {
    cout << "socket spusta" << endl;
    zak* paramt = reinterpret_cast<zak *>(parameter);
    char buffer[BUFF_N];

    /* ked sa vztvori socket vytvori sa aj toto vlakno, takze posledny socket je zatial volny
     * a toto vlakno si ho zoberie a bude pren pocuvat
     */

    int socket = paramt->socket;
    //cout << socket << endl;
    //cout << "socket funguje hadam" << endl;
    bool koniec;
    pthread_mutex_lock(paramt->server->getMutexPrekladac());
    koniec = paramt->server->getKoniec();
    pthread_mutex_unlock(paramt->server->getMutexPrekladac());

    cout << "ide citat" << endl;
    do {
        bzero(buffer, BUFF_N);
        int n = read(socket, buffer, BUFF_N - 1);

        if (n > 0){
            cout << "prisla sprava" << endl;
            cout << buffer << endl;
            pthread_mutex_lock(paramt->server->getMutexPrekladac());

            cout << "ide sa vykonat prikaz" << endl;
            string odpoved = paramt->server->getPrekladac()->rozoznaj(buffer);
            cout << "prikaz sa vykonal" << endl;
            paramt->server->posliSpravu(socket, odpoved.c_str());
            koniec = paramt->server->getKoniec();
            cout << "odpoved sa odoslala" << endl;

            pthread_mutex_unlock(paramt->server->getMutexPrekladac());

        }
    }
    while (!koniec);
}


/*
 * keď príde nové spojenie vytvorí novy socket a thread pre nového klienta
 * toto je funkcia co musi byt vlastne vlakno
 */
void* connectSpojenie(void* parameter) {
    Server* server  = reinterpret_cast<Server*>(parameter);
    sockaddr_in kliAddr{};
    socklen_t klientLength = sizeof(kliAddr);

    bool koniec = false;


    while(!koniec) {
         if(server->getKlienti_t()->size() < 20) {
             int newSocketfd = accept(server->getSocketFD(), (struct sockaddr*)&kliAddr, &klientLength);


             if (newSocketfd > 0) {
                 cout << "nove spojenie " << newSocketfd << " niekto sa napojil na server" << endl;
                 pthread_mutex_lock(server->getMutexPrekladac());

                 //cout << "mutex lock" << endl;
                 server->pridajKlienta(newSocketfd);
                 //cout << "pridava socket" << endl;
                 pthread_t vlakno_klient;

                 zak paramt;
                 paramt.server = server;
                 paramt.socket = newSocketfd;

                 pthread_create(&vlakno_klient,NULL, primacSprav, (void*) &paramt);
                 server->getKlienti_t()->push_back(vlakno_klient);
                 //cout << "vlakno sa vytvorilo a pridalo do vect" << endl;
                 koniec = server->getKoniec();
                 pthread_mutex_unlock(server->getMutexPrekladac());
                 cout << newSocketfd << " uspesne vytvorene vlakno" << endl;
             }
         }
    }
}


/*
 * zalozi sa vlakno na pripajanie klientov a ked sa niekto pripoji tak aj vlakna a socket na obsluhu klienta
 *  kazde vlakno ma vlastny buffer
 * jedna database, preto posielat spravy aj s ID uzivatela(na pracu s tabulkami)
 */
Server::Server(int port) {
    koniec = false;
    struct sockaddr_in servAddr;
    bzero((char*)&servAddr,sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(port);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(bind(socketfd,(struct sockaddr*) &servAddr, sizeof(servAddr)) < 0){
        perror("Chyba pri bindovani socketu :");
    }
    listen(socketfd, 25);

    pthread_mutex_init(&mutex_prekladac, NULL);
    pthread_create(&primac_spojeni,NULL, connectSpojenie, this);
}

/*
 * destructor zavrie sockety a joine vlakna
 */
Server::~Server() {
    // TODO asi zatvaram vlakna co este nieco robia
    for (int klient : getKlienti()) {
        shutdown(klient,SHUT_RDWR);
        close(klient);
    }
    shutdown(socketfd,SHUT_RDWR);
    close(socketfd);

    for(pthread_t klient : klienti_t){
        pthread_join(klient,NULL);
    }
    pthread_join(primac_spojeni,NULL);
}

/*
 * pridame socket klienta do vectoru klientov
 */
void Server::pridajKlienta(int klient) {
    klienti.push_back(klient);
}

/*
 * odosleme spravu naspat
 */
void Server::posliSpravu(int klientSock,string sprava) {
    int n = write(klientSock, sprava.c_str(), sprava.size() );
}

vector<int> Server::getKlienti() {
    return klienti;
}

int Server::getSocketFD() const{
    return socketfd;
}

bool Server::getKoniec() const {
    return this->koniec;
}

vector<pthread_t>* Server::getKlienti_t() {
    return &(this->klienti_t);
}

pthread_mutex_t *Server::getMutexPrekladac() {
    return &(this->mutex_prekladac);
}

PrekladacServer *Server::getPrekladac() {
    return &(this->prekladac);
}

void Server::setKoniec(bool parKoniec) {
    koniec = parKoniec;
}


#undef BUFF_N