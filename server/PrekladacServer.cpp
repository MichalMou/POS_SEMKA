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
        odpoved += vytvoreneTabUsera(spravaVektor[1]);

    } else if (spravaVektor[0] == "prst") {
        odpoved += pristupneTabUsera(spravaVektor[1]);

    } else if (spravaVektor[0] == "vytt") {
        odpoved += vytvorTab(spravaVektor[1],spravaVektor[2],spravaVektor[3],spravaVektor[4],stoi(spravaVektor[5]));

    } else if (spravaVektor[0] == "otvt") {
        if(databaza.exists(spravaVektor[1])){
            odpoved += "true";
        } else {
            odpoved += "false";
        }

    } else if (spravaVektor[0] == "zmzt") {
        odpoved += zmazTab(spravaVektor[1]);

    } else if (spravaVektor[0] == "prpp") {
        odpoved += pridajPrava(spravaVektor[1],spravaVektor[2],spravaVektor[3]);

    } else if (spravaVektor[0] == "uppp") {
        odpoved += upravPrava(spravaVektor[1],spravaVektor[2],spravaVektor[3]);

    } else if (spravaVektor[0] == "przz") {
        string data;
        for (int i = 0; i < spravaVektor.size(); i++) {
            if (i > 1 && i < (spravaVektor.size() - 1)) {
                if (i > 2) {
                    data += ",";
                }
                data += spravaVektor[i];
            }
        }

                odpoved += pridajZaznam(spravaVektor[1], data, spravaVektor.back());

    } else if (spravaVektor[0] == "akzz") {
        odpoved += aktualizujZaznam(spravaVektor[1],stoi(spravaVektor[2]),spravaVektor[3],spravaVektor[4],spravaVektor[5]);

    } else if (spravaVektor[0] == "aczz") {
        odpoved += aktualizujCelyZaznam(spravaVektor[1],stoi(spravaVektor[2]),spravaVektor[3],spravaVektor[4]);

    } else if (spravaVektor[0] == "zmzz") {
        odpoved += zmazatZaznam(spravaVektor[1],stoi(spravaVektor[2]),spravaVektor[3]);

    } else if (spravaVektor[0] == "vzzn") {
        odpoved += vypisatZaznamiNeutriedene(spravaVektor[1],spravaVektor[2]);

    } else if (spravaVektor[0] == "vzzu") {
        odpoved += vypisatZaznamiUtriedene(spravaVektor[1], stoi(spravaVektor[2]),spravaVektor[3]);

    } else if (spravaVektor[0] == "getm") {
        odpoved += getTabNazvy(spravaVektor[1]);

    } else if (spravaVektor[0] == "gett") {
        odpoved += getTabTypy(spravaVektor[1]);

    } else if (spravaVektor[0] == "regi") {
        odpoved += registruj(spravaVektor[1], spravaVektor[2]);

    } else if (spravaVektor[0] == "prih") {
        odpoved += prihlas(spravaVektor[1], spravaVektor[2]);
    }

    return odpoved;
}

string PrekladacServer::getTabNazvy(string menoTab) {
    return tabulka.getNazvyStlpcov(menoTab);
}

string PrekladacServer::getTabTypy(string menoTab) {
    return tabulka.getDatTypyStlpcov(menoTab);
}

string PrekladacServer::getTabPrava(string menoTab,string menoUser) {
    return databaza.getPristup(menoTab, menoUser);
}

string PrekladacServer::vytvoreneTabUsera(string menoUser) {
    return databaza.getZoznamTabuliekPouzivatela(menoUser);
}

string PrekladacServer::pristupneTabUsera(string menoUser) {
    return databaza.getZoznamTabuliekPouzivatelaSPristupom(menoUser);
}

string PrekladacServer::vytvorTab(string nazovTab, string nazvyStlpcov, string nazovTypov, string menoUser, int pocetStlpcov) {
    nazvyStlpcov = vymenZnak(nazvyStlpcov,'|',',');
    nazovTypov = vymenZnak(nazovTypov,'|',',');

    if(databaza.vytvorTab(nazovTab, menoUser, pocetStlpcov, nazvyStlpcov, nazovTypov)) {
        cout << "Uspesne vytvorena nova tabulka." << endl;
        return "true";
    }
    return "false";
}

string PrekladacServer::zmazTab(string nazovTab) {
    if(databaza.zrusTab(nazovTab)) {
        return "true";
    }
    return "false";
}

string PrekladacServer::upravPrava(string menoTab, string menoUser, string data) {
    if(databaza.aktualizujVsetkyPristupy(menoTab,menoUser,data)) {
        return "true";
    }
    return "false";
}

string PrekladacServer::pridajPrava(string menoTab, string menoUser, string data) {
    if(databaza.nastavPristup(menoTab,menoUser,data)) {
        return "true";
    }
    return "1false";
}

string PrekladacServer::pridajZaznam(string nazovTab, string data, string menoUser) {
    string pristup = databaza.getPristup(nazovTab,menoUser);
    vector<string> pravaVektor;
    stringstream ss(pristup);

    while (ss.good()) {
        string substr;
        getline(ss, substr, '*');
        pravaVektor.push_back(substr);
    }

    if(pravaVektor[0] == "1"){
        tabulka.pridajZaznam(nazovTab,data);
        return "Zaznam bol uspesne pridany.";
    } else {
        return "Nemas prava pridat zaznam.";
    }
}

string PrekladacServer::aktualizujZaznam(string nazovTab, int IDriadku, string nazovStlpec, string data, string menoUser) {
    string pristup = databaza.getPristup(nazovTab,menoUser);
    vector<string> pravaVektor;
    stringstream ss(pristup);
    while (ss.good()) {
        string substr;
        getline(ss, substr, '*');
        pravaVektor.push_back(substr);
    }

    if(pravaVektor[1] == "1"){
        if(tabulka.aktualizujZaznam(nazovTab,IDriadku,nazovStlpec,data)){
            return "Zaznam bol uspesne aktualizovany.";
        } else {
            return "Error nezadal si spravne parametre.";
        }
    } else {
        return "Error nemas prava pridat zaznam.";
    }
}

string PrekladacServer::aktualizujCelyZaznam(string nazovTab, int IDriadku, string data, string menoUser) {
    // separujem data ,
    string pristup = databaza.getPristup(nazovTab,menoUser);
    vector<string> pravaVektor;
    stringstream ss(pristup);
    while (ss.good()) {
        string substr;
        getline(ss, substr, '*');
        pravaVektor.push_back(substr);
    }

    if(pravaVektor[1] == "1"){
        vector<string> dataVektor;
        stringstream ssdata(data);
        while (ssdata.good()) {
            string substr;
            getline(ssdata, substr, '.');
            dataVektor.push_back(substr);
        }

        string menaStlpcov = tabulka.getNazvyStlpcov(nazovTab);
        vector<string> menaVektor;
        stringstream ssmena(menaStlpcov);
        while (ssmena.good()) {
            string substr;
            getline(ssmena, substr, ',');
            menaVektor.push_back(substr);
        }

        for(int i = 0; i < menaVektor.size(); i++){
            tabulka.aktualizujZaznam(nazovTab,IDriadku,menaVektor[i],dataVektor[i]);
        }
        return "Zaznam bol uspesne aktualizovany.";
    } else {
        return "Error nemas prava pridat zaznam.";
    }
}

string PrekladacServer::zmazatZaznam(string nazovTab, int IDriadku, string menoUser) {
    string pristup = databaza.getPristup(nazovTab,menoUser);
    vector<string> pravaVektor;
    stringstream ss(pristup);
    while (ss.good()) {
        string substr;
        getline(ss, substr, '*');
        pravaVektor.push_back(substr);
    }

    if(pravaVektor[3] == "1")
    {
        tabulka.vymazZaznam(nazovTab,IDriadku);
        return "Zaznam uspesne vymazany";
    }
    return "Error nemas prava na vymazanie zaznamu.";
}

string PrekladacServer::vypisatZaznamiNeutriedene(string nazovTab, string menoUser) {
    string pristup = databaza.getPristup(nazovTab, menoUser);
    vector<string> pravaVektor;
    stringstream ss(pristup);
    while (ss.good()) {
        string substr;
        getline(ss, substr, '*');
        pravaVektor.push_back(substr);
    }

    if (pravaVektor[2] == "1"){
        return tabulka.vypisNeutriedenejTabulky(nazovTab);
    } else {
        return "Error nemas prava na vypisanie tabulky.";
    }
}

string PrekladacServer::vypisatZaznamiUtriedene(string nazovTab, int stlpec, string menoUser) {
    string pristup = databaza.getPristup(nazovTab, menoUser);
    vector<string> pravaVektor;
    stringstream ss(pristup);
    while (ss.good()) {
        string substr;
        getline(ss, substr, '*');
        pravaVektor.push_back(substr);
    }

    if (pravaVektor[2] == "1"){
        string menaStlpcov = tabulka.getNazvyStlpcov(nazovTab);
        vector<string> menaVektor;
        stringstream ssmena(menaStlpcov);
        while (ssmena.good()) {
            string substr;
            getline(ssmena, substr, ',');
            menaVektor.push_back(substr);
        }

        return tabulka.vypisUtriedenejTabulky(nazovTab,menaVektor[stlpec]);
    } else {
        return "Error nemas prava na vypisanie tabulky.";
    }
}

string PrekladacServer::registruj(string menoUser, string heslo) {
    string zapis = menoUser + "," + heslo;
    if (databaza.jeUzivatel(zapis) > 0)
    {
        return "Error user uz existuje.";
    } else {
        databaza.zapisPouzivatela(zapis);
        return "Registracia uspesna.";
    }
}

string PrekladacServer::prihlas(string menoUser, string heslo) {
    string zapis = menoUser + "," + heslo;
    cout << databaza.jeUzivatel(zapis) << endl;
    if (databaza.jeUzivatel(zapis) > 0)
    {
        cout << "login pokus:" << zapis << endl;
        return to_string(databaza.jeUzivatel(zapis));
    } else {
        return "-1";
    }
}

string PrekladacServer::vymenZnak(string text, char hladany, char nahrada) {
    int velkost = text.size();
    for(int i = 0; i < velkost; i++) {
        if (text[i] == hladany) {
            text[i] = nahrada;
        }
    }
    return text;
}

