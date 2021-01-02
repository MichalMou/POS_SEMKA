#include "Server.h"

using namespace std;

#define BUFF_N 1024


// TODO prerobit
void* primacSprav(void* parameter) {
    Server *server = reinterpret_cast<Server *>(parameter);
    char buffer[BUFF_N];

    do {
        for(int newSock : *server->getKlienti()){
            bzero(buffer, BUFF_N);
            int n = read(newSock, buffer, BUFF_N - 1);
            if (n > 0){
                // na testovanie cout << "mam spravu: " << buffer << endl;
                // TODO funkcionalita
                /*
                 * daky string odpoved = server.getPrekladac().prelozaVykonajTabOperaciu(buffer)
                 */
                (*server->getMutexPrekladac()).


                // TODO rovno aj odpoveda
                // server->posliSpravu(newSock, odpoved);
            }
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

    while(!server->getKoniec() && server->getKlienti_t()->size() < 20) {
        int newSocketfd = accept(server->getSocketFD(), (struct sockaddr*)&kliAddr, &klientLength);

        if (newSocketfd > 0) {
            server->pridajKlienta(newSocketfd);

            pthread_t vlakno_klient;
            server->getKlienti_t()->push_back(vlakno_klient);
            pthread_create(&(server->getKlienti_t()->back()),NULL, primacSprav, server);
        }
    }
}


/*
 * zalozi sa vlakno na pripajanie klientov a ked sa niekto pripoji tak aj vlakna a socket na obsluhu klienta
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


    // TODO pthred
    /* socket je priamo UID
     * kazde vlakno ma vlastny buffer
     * jedna database, preto posielat spravy aj s ID uzivatela(na pracu s tabulkami)
     *
     * 1.1thread bude pocuvat a robit nove spojenia + novy thread ked sa niekto pripoji :)
     *
     * 2.zoznam threadov pre klientov :)
     *
     * 3.ak je sprava privelka napisat ze zly prikaz a sprava je privelka, teoreticky to moze robit aj prekladac
     *
     * 4.jeden prekladac a jedna DB pre vsetky vlakna obsluhovany mutexom
     */

}

Server::~Server() {
    for (int klient : *getKlienti()) {
        close(klient);
    }
    // TODO delete thready
    // pthread_join(sprava,NULL);
    delete klienti;
    close(socketfd);
}

int Server::getSocketFD() const{
    return socketfd;
}

void Server::pridajKlienta(int klient) {
    klienti->push_back(klient);
}

void Server::posliSpravu(int klientSock, char * sprava) {
    // TODO osetrit ze sprava je max velkosti buffer
    int n = write(klientSock,sprava,strlen(sprava) + 1);
}

const vector<int> *Server::getKlienti() {
    return this->klienti;
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

string Server::funkcionalitaDB(string sprava) {


    return std::__cxx11::string();
}


#undef BUFF_N