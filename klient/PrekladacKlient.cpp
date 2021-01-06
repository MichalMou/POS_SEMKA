//
// Created by Michal on 6. 1. 2021.
//

#include "PrekladacKlient.h"

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
 * prime odpoved na spravu ""
 */
string PrekladacKlient::primiOdpovedNaSpravu(string sprava) {
    char* poslat = (char*)"";
    strcat(poslat,sprava.c_str());

    string odpoved;
    odpoved = klient->precitaj(poslat);
    if(odpoved != "x"){ }


    return odpoved;
}





/*
 * vrati string obsahujuci vytvorene Tabulky
 * kod:mojt
 */
string PrekladacKlient::vytvorene_Tab(string userName) {
    string sprava = "mojt,";
    string odpoved;

    sprava += userName;

    posliSpravu(sprava);
    odpoved = primiOdpovedNaSpravu(sprava);

    return odpoved;
}

/* zapise do usera v kt tabulke je
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
 * vytT
 */
bool PrekladacKlient::vytvorTab(string meno, string dataTypy, string dataNazvy) {
    string sprava = "prst,";
    string odpoved;

    sprava += meno;
    sprava += dataTypy;
    sprava += dataNazvy;

    posliSpravu(sprava);
    odpoved = primiOdpovedNaSpravu(sprava);

    // TODO rozlustenie odpovedi

    return odpoved;
}

/*
 * otvT
 */
bool PrekladacKlient::otvorTab(string nazovTab) {
    return false;
}

/*
 * kod:zmzt
 */
bool PrekladacKlient::zmazTab(string nazovTab, string userName) {
    return false;
}

/*
 * kod:prpp
 */
bool PrekladacKlient::pridajPristupovePrava(string meno, string prava, string menoZadavatel) {
    return false;
}

/*
 * kod:uppr
 */
bool PrekladacKlient::upravPrava(string nazovTab, string menoPouzivatela, string data_prava) {
    return false;
}

/*
 * kod:przz
 */
bool PrekladacKlient::pridajZaznam() {
    return false;
}

/*
 * kod:akzz
 */
bool PrekladacKlient::aktualizovatZaznam() {
    return false;
}

/*
 * kod:zmzz
 */
bool PrekladacKlient::zmazatZaznam(string nazovTab, int IDriadku) {
    return false;
}

/*
 * kod:vzzn
 */
string PrekladacKlient::vypisatZaznamiNeutriedene(string nazovTab) {
    return std::__cxx11::string();
}

/*
 * kod:vzzu
 */
string PrekladacKlient::vypisatZaznamiUtriedene(int stlpec) {
    return std::__cxx11::string();
}
