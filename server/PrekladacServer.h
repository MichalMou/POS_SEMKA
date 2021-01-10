//
// Created by Michal on 7. 1. 2021.
//

#ifndef UNTITLED6_PREKLADACSERVER_H
#define UNTITLED6_PREKLADACSERVER_H

#include <string>
#include <istream>
#include "../databaza/Databaza.h"
#include "../tabulka/Tabulka.h"

using namespace std;

class PrekladacServer {
public:
    string registruj(string menoUser, string heslo);
    string prihlas(string menoUser, string heslo);

    string getTabNazvy(string menoTab);
    string getTabTypy(string menoTab);
    string getTabPrava(string menoTab,string menoUser);

    string rozoznaj(string sprava);

    string vytvoreneTabUsera(string menoUser);
    string pristupneTabUsera(string menoUser);

    string vytvorTab(string nazovTab, string nazvyStlpcov, string nazovTypov, string menoUser, int pocetStlpcov);
    string zmazTab(string nazovTab);

    string pridajPrava(string menoTab, string menoUser, string data);
    string upravPrava(string menoTab, string menoUser, string data);

    string pridajZaznam(string nazovTab, string data, string menoUser);
    string aktualizujZaznam(string nazovTab, int IDriadku, string nazovStlpec, string data, string menoUser);// ====== zlozite ak chceme viacej udajov prepisat tak
    string aktualizujCelyZaznam(string nazovTab, int IDriadku, string data, string menoUser);
    string zmazatZaznam(string nazovTab, int IDriadku, string menoUser);// ======= kontrola ci ma prava
    string vypisatZaznamiNeutriedene(string nazovTab, string menoUser);
    string vypisatZaznamiUtriedene(string nazovTab, int stlpec, string menoUser);// ===== musi sa najprv pytat na to ake typy ma a potom sa opyta usera podla kt z nich chce triedit

    string vymenZnak(string text, char hladany, char nahrada);
private:
    Databaza databaza;
    Tabulka tabulka;
};


#endif //UNTITLED6_PREKLADACSERVER_H
