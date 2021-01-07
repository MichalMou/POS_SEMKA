//
// Created by Michal on 6. 1. 2021.
//

#include "PrekladacKlient.h"

using namespace std;

PrekladacKlient::PrekladacKlient(User* parUser, Klient* parKlient) {
    user = parUser;
    klient = parKlient;
}

PrekladacKlient::~PrekladacKlient() {

}

/*
 * posle spravu cez klienta na server
 */
void PrekladacKlient::posliSpravu(string sprava) {
    char* poslat = (char*)"";
    strcat(poslat,sprava.c_str());

    klient->posliSpravu(poslat);
}

/*
 * prime odpoved na spravu
 */
string PrekladacKlient::primiOdpovedNaSpravu(string sprava) {
    char* poslat = (char*)"";
    strcat(poslat,sprava.c_str());

    string odpoved;
    odpoved = klient->precitaj(poslat);

    int spravaLength = sprava.size();
    odpoved = odpoved.substr(spravaLength, odpoved.size() - spravaLength - 1);

    return odpoved;
}

/*
 * vrati string obsahujuci vytvorene Tabulky
 * kod:mojt
 */
string PrekladacKlient::vytvorene_Tab(string userName) {
    string sprava = "mojt,";
    sprava += userName;

    posliSpravu(sprava);

    string odpoved;
    odpoved = primiOdpovedNaSpravu(sprava);

    return odpoved;
}

/*
 * zapise do usera v kt tabulke je
 * kod:prst
 */
string PrekladacKlient::pristupene_Tab(string userName) {
    string sprava = "prst,";
    string odpoved;

    sprava += userName;

    posliSpravu(sprava);
    odpoved = primiOdpovedNaSpravu(sprava);

    return odpoved;
}

/*
 * vytvori Tabulku s zadanymi param
 * vytt
 */
bool PrekladacKlient::vytvorTab(string meno, string dataTypy, string dataNazvy) {
    string sprava = "vytt,";
    string odpoved;

    sprava += meno;
    sprava += dataTypy;
    sprava += dataNazvy;

    posliSpravu(sprava);
    odpoved = primiOdpovedNaSpravu(sprava);

    if(odpoved.compare("true") == 0)
    {
        return true;
    }
    return false;
}

/*
 * otvt
 */
bool PrekladacKlient::otvorTab(string nazovTab) {
    string sprava = "otvt,";
    sprava += nazovTab;

    posliSpravu(sprava);

    string odpoved;
    odpoved = primiOdpovedNaSpravu(sprava);

    if(odpoved.compare("true") == 0)
    {
        user->setMenoUpravovanejTab(nazovTab);
        return true;
    }
    return false;
}

/* vymaze tabulku
 * kod:zmzt
 */
bool PrekladacKlient::zmazTab(string nazovTab, string userName) {
    string sprava = "zmzt,";
    sprava += nazovTab;

    posliSpravu(sprava);

    string odpoved;
    odpoved = primiOdpovedNaSpravu(sprava);

    if(odpoved.compare("true") == 0)
    {
        user->setMenoUpravovanejTab(nullptr);
        return true;
    }
    return false;
}

/* prida pristupove prava k tabulke
 * kod:prpp
 */
bool PrekladacKlient::pridajPristupovePrava(string meno, string prava) {
    string sprava = "prpp,";
    sprava += meno;
    sprava += prava;

    posliSpravu(sprava);

    string odpoved;
    odpoved = primiOdpovedNaSpravu(sprava);

    if(odpoved.compare("true") == 0)
    {
        return true;
    }
    return false;
}

/*
 * kod:uppr
 */
bool PrekladacKlient::upravPrava(string menoPouzivatela, string data_prava) {
    string sprava = "uppp,";
    sprava += user->getMenoUpravovanejTab();
    sprava += menoPouzivatela;
    sprava += data_prava;

    posliSpravu(sprava);

    string odpoved;
    odpoved = primiOdpovedNaSpravu(sprava);

    if(odpoved.compare("true") == 0)
    {
        return true;
    }
    return false;}

/*
 * kod:przz
 */
bool PrekladacKlient::pridajZaznam(string zaznam) {
    string sprava = "przz." + user->getMenoUpravovanejTab() + zaznam;
    posliSpravu(sprava);

    string odpoved;
    odpoved = primiOdpovedNaSpravu(sprava);

    if(odpoved.compare("true") == 0)
    {
        return true;
    }
    return false;
}

/*
 * kod:akzz
 */
bool PrekladacKlient::aktualizovatZaznam(string zaznam) {
    string sprava = "akzz." + user->getMenoUpravovanejTab() + zaznam;
    posliSpravu(sprava);

    string odpoved;
    odpoved = primiOdpovedNaSpravu(sprava);

    if(odpoved.compare("true") == 0)
    {
        return true;
    }
    return false;
}

/*
 * kod:zmzz
 */
bool PrekladacKlient::zmazatZaznam(int IDriadku) {
    string sprava = "zmzz." + user->getMenoUpravovanejTab() + to_string(IDriadku);
    posliSpravu(sprava);

    string odpoved;
    odpoved = primiOdpovedNaSpravu(sprava);

    if(odpoved.compare("true") == 0)
    {
        return true;
    }
    return false;
}

/*
 * kod:vzzn
 */
string PrekladacKlient::vypisatZaznamiNeutriedene() {
    string sprava = "vzzn." + user->getMenoUpravovanejTab();
    posliSpravu(sprava);

    string odpoved;
    odpoved = primiOdpovedNaSpravu(sprava);

    return odpoved;
}

/*
 * kod:vzzu
 */
string PrekladacKlient::vypisatZaznamiUtriedene(int stlpec) {
    string sprava = "vzzu." + user->getMenoUpravovanejTab();
    sprava += to_string(stlpec);
    posliSpravu(sprava);

    string odpoved;
    odpoved = primiOdpovedNaSpravu(sprava);

    return odpoved;
}

/*
 * kod:getm
 */
string PrekladacKlient::getMenaSTabulky() {
    string sprava = "getm." + user->getMenoUpravovanejTab();
    posliSpravu(sprava);

    string odpoved;
    odpoved = primiOdpovedNaSpravu(sprava);

    return odpoved;
}

/*
 * kod:gett
 */
string PrekladacKlient::getTypySTabulky() {
    string sprava = "gett." + user->getMenoUpravovanejTab();
    posliSpravu(sprava);

    string odpoved;
    odpoved = primiOdpovedNaSpravu(sprava);

    return odpoved;
}
