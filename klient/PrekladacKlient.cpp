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

    klient->posliSpravu(sprava);
}

/*
 * prime odpoved na spravu
 */
string PrekladacKlient::primiOdpovedNaSpravu(string sprava) {
    string odpoved;

    sleep(3);

    odpoved = klient->precitaj(sprava);

    int spravaLength = sprava.size();
    odpoved = odpoved.substr(spravaLength + 1, odpoved.size() - spravaLength - 1);

    return odpoved;
}

/*
 * vrati string obsahujuci vytvorene Tabulky
 * kod:mojt
 */
string PrekladacKlient::vytvorene_Tab(string userName) {
    string sprava = "mojt,";
    sprava += userName;

    string odpoved;
    posliSpravu(sprava);

    odpoved = primiOdpovedNaSpravu(sprava);

    return odpoved;
}

/*
 * zapise do usera v kt tabulke je
 * kod:prst
 */
string PrekladacKlient::pristupene_Tab(string userName) {
    string sprava = "prst,";
    sprava += userName;

    posliSpravu(sprava);

    string odpoved;
    odpoved = primiOdpovedNaSpravu(sprava);

    return odpoved;
}

/*
 * vytvori Tabulku s zadanymi param
 * vytt
 */
bool PrekladacKlient::vytvorTab(string meno, string dataTypy, string dataNazvy, int pocStlpcov) {
    string sprava = "vytt,";
    sprava += meno;
    sprava += ",";
    sprava += dataNazvy;
    sprava += ",";
    sprava += dataTypy;
    sprava += ",";
    sprava += user->getMeno();
    sprava += ",";
    sprava += to_string(pocStlpcov);
    cout << sprava;

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
        user->setMenoUpravovanejTab("");
        return true;
    }
    return false;
}

/* prida pristupove prava k tabulke
 * kod:prpp
 */
bool PrekladacKlient::pridajPristupovePrava(string meno, string prava, string menoTab) {
    string sprava = "prpp,";
    sprava += menoTab;
    sprava += ",";
    sprava += meno;
    sprava += ",";
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
    sprava += ",";
    sprava += menoPouzivatela;
    sprava += ",";
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
    string sprava = "przz," + user->getMenoUpravovanejTab() + "," + zaznam;
    sprava += ",";
    sprava += user->getMeno();
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
bool PrekladacKlient::aktualizovatZaznam(string zaznam, int cisloRiadku, string menoStlpca) {
    string sprava = "akzz," + user->getMenoUpravovanejTab() + "," + to_string(cisloRiadku);
    sprava += ",";
    sprava += menoStlpca;
    sprava += ",";
    sprava += zaznam;
    sprava += ",";
    sprava += user->getMeno();
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
 * kod:aczz
 */
bool PrekladacKlient::aktualizovatCelyZaznam(string zaznam, int cisloRiadku) {
    string sprava = "aczz," + user->getMenoUpravovanejTab() + "," + to_string(cisloRiadku);
    sprava += ",";
    sprava += zaznam;
    sprava += ",";
    sprava += user->getMeno();
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
    string sprava = "zmzz," + user->getMenoUpravovanejTab() + "," + to_string(IDriadku);
    sprava += ",";
    sprava += user->getMeno();
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
    string sprava = "vzzn," + user->getMenoUpravovanejTab();
    sprava += ",";
    sprava += user->getMeno();
    posliSpravu(sprava);

    string odpoved;
    odpoved = primiOdpovedNaSpravu(sprava);

    return odpoved;
}

/*
 * kod:vzzu
 */
string PrekladacKlient::vypisatZaznamiUtriedene(int stlpec) {
    string sprava = "vzzu," + user->getMenoUpravovanejTab() + ",";
    sprava += to_string(stlpec);
    sprava += ",";
    sprava += user->getMeno();
    posliSpravu(sprava);

    string odpoved;
    odpoved = primiOdpovedNaSpravu(sprava);

    return odpoved;
}

/*
 * kod:getm
 */
string PrekladacKlient::getMenaTabulky() {
    string sprava = "getm," + user->getMenoUpravovanejTab();
    posliSpravu(sprava);

    string odpoved;
    odpoved = primiOdpovedNaSpravu(sprava);

    return odpoved;
}

/*
 * kod:gett
 */
string PrekladacKlient::getTypyTabulky() {
    string sprava = "gett," + user->getMenoUpravovanejTab();
    posliSpravu(sprava);

    string odpoved;
    odpoved = primiOdpovedNaSpravu(sprava);

    return odpoved;
}

/*
 * kod:regi
 */
string PrekladacKlient::registruj(string menoUser, string heslo) {
    string sprava = "regi," + menoUser;
    sprava += ",";
    sprava += heslo;
    posliSpravu(sprava);

    string odpoved;
    odpoved = primiOdpovedNaSpravu(sprava);

    return odpoved;
}

/*
 * kod:prih
 */
string PrekladacKlient::prihlas(string menoUser, string heslo) {
    string sprava = "prih," + menoUser;
    sprava += ",";
    sprava += heslo;

    posliSpravu(sprava);
    string odpoved;
    odpoved = primiOdpovedNaSpravu(sprava);

    return odpoved;
}
