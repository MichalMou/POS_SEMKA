#include <search.h>
#include "Server.h"

using namespace std;

#define BUFF_N 1024

/*
 * TODO robi iba s vlaknom ktore mu bolo dane preto mame vlakno+primacSprav pre kazdy socket
 * funkcionalita vlakna
 * bude citat prichadzajuce spravy a davať ich prekladacu a potom posle vysledok naspet
 */
void* primacSprav(void* parameter) {
    Server *server = reinterpret_cast<Server *>(parameter);
    char buffer[BUFF_N];

    /* ked sa vztvori socket vytvori sa aj toto vlakno, takze posledny socket je zatial volny
     * a toto vlakno si ho zoberie a bude pren pocuvat */
    int socket = server->getKlienti_t()->back();

    do {
        bzero(buffer, BUFF_N);
        int n = read(socket, buffer, BUFF_N - 1);
        if (n > 0){
            pthread_mutex_lock(server->getMutexPrekladac());
            /*
             * na testovanie //// cout << "mam spravu: " << buffer << endl;
             * TODO funkcionalita
             * daky string odpoved = server.getPrekladac().prelozaVykonajTabOperaciu(buffer
             * TODO vrati odpoved
             * server->posliSpravu(newSock, odpoved);
             */
            pthread_mutex_unlock(server->getMutexPrekladac());
        }
    }
    while (!server->getKoniec());
}


/*
 * keď príde nové spojenie vytvorí novy socket a thread pre nového klienta
 * toto je funkcia co musi byt vlastne vlakno
 */
void* connectSpojenie(void* parameter) {
    Server* server  = reinterpret_cast<Server*>(parameter);
    struct sockaddr_in kliAddr;
    socklen_t klientLength = sizeof(kliAddr);

    while(!server->getKoniec()) {
         if(server->getKlienti_t()->size() < 20) {
             int newSocketfd = accept(server->getSocketFD(), (struct sockaddr*)&kliAddr, &klientLength);

             if (newSocketfd > 0) {
                 pthread_mutex_lock(server->getMutexPrekladac());

                 server->pridajKlienta(newSocketfd);
                 pthread_t vlakno_klient;
                 server->getKlienti_t()->push_back(vlakno_klient);
                 pthread_create(&(server->getKlienti_t()->back()),NULL, primacSprav, server);

                 pthread_mutex_unlock(server->getMutexPrekladac());
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

    // mutex na obsluhu prekladaca a databazy
    pthread_mutex_init(&mutex_prekladac, NULL);
    // thread co obsluhuje vytvorenie novych spojeni
    pthread_create(&primac_spojeni,NULL, connectSpojenie, this);


    // TODO mutex a funkcionalita
    /* socket je priamo UID

     *
     * 1.1thread bude pocuvat a robit nove spojenia + novy thread ked sa niekto pripoji :)
     *
     * 2.zoznam threadov pre klientov :)
     *
     * 3.ak je sprava privelka napisat ze zly prikaz a sprava je privelka, teoreticky to moze robit aj prekladac :)
     *
     * 4.jeden prekladac a jedna DB pre vsetky vlakna obsluhovany mutexom
     */
}

/*
 * destructor zavrie sockety a joine vlakna
 */
Server::~Server() {
    for (int klient : *getKlienti()) {
        close(klient);
    }
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
    klienti->push_back(klient);
}

/*
 * odosleme spravu naspat
 */
void Server::posliSpravu(int klientSock, char * sprava) {
    // TODO osetrit ze sprava je max velkosti buffer
    int n = write(klientSock,sprava,strlen(sprava) + 1);
}

/*
 * sprava sa preda prekladacu a vykona v DB, potom sa vrati string vysledok
 */
string Server::funkcionalitaDB(string sprava) {
    return std::__cxx11::string();
}

const vector<int> *Server::getKlienti() {
    return this->klienti;
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


#undef BUFF_N