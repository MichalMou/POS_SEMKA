//
// Created by Michal on 6. 1. 2021.
//

#ifndef UNTITLED6_PREKLADACKLIENT_H
#define UNTITLED6_PREKLADACKLIENT_H

#include <string>

#include <string.h>
#include "../User/User.h"
#include "klient.h"

using namespace std;

class PrekladacKlient {
public:
    PrekladacKlient(User* parUser, Klient* parKlient);
    ~PrekladacKlient();

    void posliSpravu(string sprava);
    string primiOdpovedNaSpravu(string sprava);

    string vytvorene_Tab(string userName);
    string pristupene_Tab(string userName);

    bool vytvorTab(string meno, string dataTypy, string dataNazvy);
    bool otvorTab(string nazovTab);

    bool zmazTab(string nazovTab, string userName);

    bool pridajPristupovePrava(string meno , string prava, string menoZadavatel); // ==== meno si môžem potom dohladat;
    bool upravPrava(string nazovTab, string menoPouzivatela, string data_prava); // ==== ja si na strane Servera okontrolujem Zadavatela

    bool pridajZaznam(); //==== funkcia sa spyta na nazvy a typy dat
    bool aktualizovatZaznam(); // === potrebuje nazov Tab, ID riadku, nazovStlpca, data ====== urobit aj funkciu pre upravu celeho riadku naraz
    bool zmazatZaznam(string nazovTab,int IDriadku); // ====== pokial je user zada 0 vymaze vsetky zaznamy, urobit kontrolu prav usera pomocou getPravaUser;
    string vypisatZaznamiNeutriedene(string nazovTab);
    string vypisatZaznamiUtriedene(int stlpec); // (podla dakeho stlpca) ===== musi sa najprv pytat na to ake typy ma a potom sa opyta usera podla kt z nich chce triedit



private:
    Klient* klient;
    User* user;
};


#endif //UNTITLED6_PREKLADACKLIENT_H
