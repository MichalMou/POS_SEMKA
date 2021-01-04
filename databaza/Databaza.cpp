//
// Created by Pocitac on 2.1.2021.
//


#include "Databaza.h"

Databaza::Databaza() {

}

Databaza::~Databaza() {

}

bool Databaza::vytvorTab(const string& nazovTabulky,const string& menoPouzivatela,int pocetStlpcov, const string& nazvyStlcov, const string& datoveTypy) {
    if (exists(nazovTabulky)) {
        return false;
    }

    if (jeUzivatel(menoPouzivatela) > 0) {
        if (pocetStlpcov > 1) {

            fstream fout;
            fstream pristupy;
            string nazovPristupov = "pristupy_" + nazovTabulky;

            fout.open(nazovTabulky, ios::out | ios::app);
            fout << menoPouzivatela << endl;
            fout << "ID," << nazvyStlcov << endl;
            fout << "int," << datoveTypy << endl;
            fout.close();

            pristupy.open(nazovPristupov, ios::out | ios::app);
            pristupy << "Meno,vkladanie,aktualizovanie,vypisovanie,mazanie" << endl;
            pristupy << menoPouzivatela << "," << "1,1,1,1" << endl;

            return true;
        } else {
            cout << "Minimalny pocet stlpcov je 2" << endl;
            return false;
        }
    }
    return false;
}

bool Databaza::zrusTab(const string& nazovTabulky) {
    if (exists(nazovTabulky)) {
        string pristupy = "pristupy_" + nazovTabulky;
        unlink((nazovTabulky).c_str());
        unlink(pristupy.c_str());
        return true;
    }
    return false;
}

bool Databaza::exists(const string& nazovTabulky) {
        ifstream f((nazovTabulky).c_str());
        return f.good();
}

int Databaza::jeUzivatel(const string & udaje) {
    fstream fout;
    string riadok;
    string idString;
    int id;
    const string & subor = "logins.csv";

    fout.open(subor, ios::in);

    while(getline(fout, riadok)) {
        stringstream s(riadok);
        if (riadok.find(udaje) != string::npos) {
            getline(s, idString, ',');
            id = stoi(idString);
            return id;
        }
    }
    return 0;
}

void Databaza::zapisPouzivatela(const string &udaje) {
    const string & subor = "logins.csv";
    string riadok;
    fstream fout;
    int count = 0;

    ifstream suborA(subor);

    while (getline(suborA, riadok)) {
        ++count;
    }

    fout.open(subor,ios::out | ios::app);

    fout << count + 1 << "," << udaje << endl;

    fout.close();
}

bool Databaza::nastavPristup(const string &menoPouzivatela, const string &nazovTabulky, const string &dataPristupov) {
    fstream fin,fout;
    stringstream temp;
    string line, word, meno, stlpce, typy;
    string riadok;
    const string & pristupy = "pristupy_" + nazovTabulky;

    if(!exists(pristupy)) {
        return false;
    }

    if(jeUzivatel(menoPouzivatela) > 0) {
        fout.open(pristupy,ios::out | ios::app);
        fout << menoPouzivatela << "," << dataPristupov << endl;
    }

    return true;
}

bool Databaza::aktualizujPristup(const string &menoPouzivatela, const string &nazovTabulky, const string &dataPristupov) {
    // TODO
    return false;
}



