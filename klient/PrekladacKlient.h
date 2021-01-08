//
// Created by Michal on 6. 1. 2021.
//

#ifndef UNTITLED6_PREKLADACKLIENT_H
#define UNTITLED6_PREKLADACKLIENT_H

#include <string>

#include <string.h>
#include <iostream>
#include "../User/User.h"
#include "klient.h"

using namespace std;

class PrekladacKlient {
public:
    PrekladacKlient(User* parUser, Klient* parKlient);
    ~PrekladacKlient();

    void posliSpravu(string sprava);
    string primiOdpovedNaSpravu(string sprava);

    string registruj(string menoUser, string heslo);
    string prihlas(string menoUser, string heslo);


    string vytvorene_Tab(string userName);
    string pristupene_Tab(string userName);

    bool vytvorTab(string meno, string dataTypy, string dataNazvy, int pocStlpcov);
    bool otvorTab(string nazovTab);
    bool zmazTab(string nazovTab, string userName);

    bool pridajPristupovePrava(string meno , string prava);
    bool upravPrava(string menoPouzivatela, string data_prava);

    bool pridajZaznam(string zaznam);
    bool aktualizovatZaznam(string zaznam, int cisloRiadku, int cislostlpca);
    bool aktualizovatCelyZaznam(string zaznam,  int cisloRiadku);
    bool zmazatZaznam(int IDriadku);
    string vypisatZaznamiNeutriedene( );
    string vypisatZaznamiUtriedene(int stlpec);

    string getMenaTabulky();
    string getTypyTabulky();


private:
    Klient* klient;
    User* user;
};


#endif //UNTITLED6_PREKLADACKLIENT_H
