//
// Created by Michal on 7. 1. 2021.
//

#include "PrekladacServer.h"

string PrekladacServer::rozoznaj(string sprava) {
    string odpoved = sprava;
    odpoved += ".";

    string str = sprava;
    vector<string> spravaVektor;
    stringstream ss(str);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        spravaVektor.push_back(substr);
    }


    if (spravaVektor[0] == "mojt"){
        // TODO ako mi to vracia tabulky
        odpoved += vytvoreneTabUsera(spravaVektor[1]);

    } else if (spravaVektor[0] == "prst") {
        odpoved += pristupneTabUsera(spravaVektor[1]);

    } else if (spravaVektor[0] == "vytt") {
        odpoved += vytvorTab(spravaVektor[1],spravaVektor[2],spravaVektor[3],spravaVektor[4]);

    } else if (spravaVektor[0] == "otvt") {
        // TODO existuje tabulka ?

    } else if (spravaVektor[0] == "zmzt") {
        odpoved += zmazTab(spravaVektor[1]);

    } else if (spravaVektor[0] == "prpp") {
        odpoved += pridajPrava(spravaVektor[1],spravaVektor[2],spravaVektor[3]);

    } else if (spravaVektor[0] == "uppp") {
        odpoved += upravPrava(spravaVektor[1],spravaVektor[2],spravaVektor[3]);

    } else if (spravaVektor[0] == "przz") {
        odpoved += pridajZaznam(spravaVektor[1],spravaVektor[2]);

    } else if (spravaVektor[0] == "akzz") {
        odpoved += aktualizujZaznam(spravaVektor[1],stoi(spravaVektor[2]),spravaVektor[3],spravaVektor[4]);

    } else if (spravaVektor[0] == "zmzz") {
        odpoved += zmazatZaznam(spravaVektor[1],stoi(spravaVektor[2]),spravaVektor[3]);

    } else if (spravaVektor[0] == "vzzn") {
        odpoved += vypisatZaznamiNeutriedene(spravaVektor[1]);

    } else if (spravaVektor[0] == "vzzu") {
        odpoved += vypisatZaznamiUtriedene(spravaVektor[1], stoi(spravaVektor[2]));

    } else if (spravaVektor[0] == "getm") {
        odpoved += getTabNazvy(spravaVektor[1]);

    } else if (spravaVektor[0] == "gett") {
        odpoved += getTabTypy(spravaVektor[1]);
    }

    return odpoved;
}

string PrekladacServer::getTabNazvy(string menoTab) {
    // TODO treba funkciu povedat Mirovi
}

string PrekladacServer::getTabTypy(string menoTab) {
    //TODO treba funkciu povedat Mirovi
}

string PrekladacServer::getTabPrava(string menoTab,string menoUser) {
    return databaza.getPristup(menoTab, menoUser);
}

string PrekladacServer::vytvoreneTabUsera(string menoUser) {
    return databaza.getZoznamTabuliekPouzivatela(menoUser);
}

string PrekladacServer::pristupneTabUsera(string menoUser) {
    //TODO treba sa opytat v akom formate to vypisuje tabulku
    return databaza.
}

string PrekladacServer::vytvorTab(string nazovTab, string nazvyStlpcov, string nazovTypov, string menoUser, int pocetStlpcov) {
    if(databaza.vytvorTab(nazovTab, menoUser, pocetStlpcov, nazvyStlpcov, nazovTypov)) {
        return ".true";
    }
    return ".false";
}

string PrekladacServer::zmazTab(string nazovTab) {
    if(databaza.zrusTab(nazovTab)) {
        return ".true";
    }
    return ".false";
}

string PrekladacServer::upravPrava(string menoTab, string menoUser, string data) {
    if(databaza.aktualizujVsetkyPristupy(menoTab,menoUser,data)) {
        return ".true";
    }
    return ".false";
}

string PrekladacServer::pridajPrava(string menoTab, string menoUser, string data) {
    if(databaza.nastavPristup(menoTab,menoUser,data)) {
        return ".true";
    }
    return ".false";
}

string PrekladacServer::pridajZaznam(string nazovTab, string data, string menoUser) {
    //TODO skontroluj prava
    string pristup = databaza.getPristup(nazovTab,menoUser);
    tabulka.pridajZaznam(nazovTab,data);

}

string PrekladacServer::aktualizujZaznam(string nazovTab, int IDriadku, string nazovStlpec, string data, string menoUser) {

}

string PrekladacServer::zmazatZaznam(string nazovTab, int IDriadku, string menoUser) {

}

string PrekladacServer::vypisatZaznamiNeutriedene(string nazovTab, string menoUser) {

}

string PrekladacServer::vypisatZaznamiUtriedene(string nazovTab, int stlpec, string menoUser) {

}

