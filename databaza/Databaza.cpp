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
            fstream zoznam;
            string nazovPristupov = "pristupy_" + nazovTabulky;

            fout.open(nazovTabulky, ios::out | ios::app);
            fout << menoPouzivatela << endl;
            fout << "ID," << nazvyStlcov << endl;
            fout << "int," << datoveTypy << endl;
            fout.close();

            pristupy.open(nazovPristupov, ios::out | ios::app);
            pristupy << "Meno,vkladanie,aktualizovanie,vypisovanie,mazanie" << endl;
            pristupy << menoPouzivatela << "," << "1*1*1*1" << endl;

            pristupy.close();

            zoznam.open("ZoznamTabuliek.csv", ios::out | ios::app);
            zoznam << menoPouzivatela << "," << nazovTabulky << endl;

            zoznam.close();

            return true;
        } else {
            cout << "Minimalny pocet stlpcov je 2" << endl;
            return false;
        }
    }
    return false;
}

bool Databaza::zrusTab(const string& nazovTabulky) {
    fstream fin;
    fstream fout;
    string riadok;
    vector<string> row;

    if (exists(nazovTabulky)) {
        string pristupy = "pristupy_" + nazovTabulky;
        unlink((nazovTabulky).c_str());
        unlink(pristupy.c_str());

        fin.open("ZoznamTabuliek.csv", ios::in);
        fout.open("new.csv", ios::out);

        while (getline(fin, riadok)) {
            row.push_back(riadok);
        }

        for (int i = 0; i < row.size(); ++i) {
            if (row[i].find(nazovTabulky) == std::string::npos) {
                fout << row[i] << endl;
            }
        }

        fin.close();
        fout.close();

        remove("ZoznamTabuliek.csv");
        rename("new.csv", "ZoznamTabuliek.csv");

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

bool Databaza::nastavPristup(const string &nazovTabulky, const string &menoPouzivatela, const string &dataPristupov) {
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

bool Databaza::aktualizujVsetkyPristupy(const string &nazovTabulky, const string &menoPouzivatela, const string &dataPristupov) {

    fstream fin,fout;
    vector<string> row;
    string riadok;
    string word;
    stringstream s;
    const string& pristupy = "pristupy_" + nazovTabulky;

    if(!exists(nazovTabulky)) {
        return false;
    }

    fin.open(pristupy, ios::in);
    fout.open("new.csv", ios::out);

    getline(fin, riadok);
    fout << riadok << endl;

    while(!fin.eof()) {
        row.clear();

        while (getline(fin, riadok, '\n')) {
            row.push_back(riadok);
        }
        for (int i = 0; i < row.size(); ++i) {
            s.str("");
            s << row[i];
            getline(s,word,',');
            if (word == menoPouzivatela) {
                fout << menoPouzivatela << "," << dataPristupov << endl;
            } else {
                fout << row[i] << endl;
            }
        }
    }

    fin.close();
    fout.close();

    remove(pristupy.c_str());
    rename("new.csv", pristupy.c_str());

    return true;
}

string Databaza::getPristup(const string &nazovTabulky, const string &menoPouzivatela) {

    fstream fout;
    string riadok;
    string word;
    vector<string> row;
    const string& pristupy = "pristupy_" + nazovTabulky;
    stringstream s;

    fout.open(pristupy, ios::in);

    getline(fout, riadok);

    if(!exists(nazovTabulky)) {
        return "Tabulka neexistuje";
    }

    while(!fout.eof()) {
        while (getline(fout, riadok, '\n')) {
            row.push_back(riadok);
        }

        for (int i = 0; i < row.size(); ++i) {
            s.str("");
            s << row[i];
            getline(s,word,',');
            if (word == menoPouzivatela) {
                getline(s, word);
                return word;
            }
        }
    }

    fout.close();

    return "Nenasiel sa";
}

string Databaza::getZoznamTabuliekPouzivatela(const string &menoPouzivatela) {
    fstream fin;
    string nazov;
    fin.open("ZoznamTabuliek.csv", ios::in);
    vector<string> row;
    string riadok;
    string vystup;

    while (getline(fin, riadok, '\n')) {
        row.push_back(riadok);
    }

    for (int i = 0; i < row.size(); ++i) {

        if (row[i].find(menoPouzivatela) != std::string::npos) {
            stringstream s;
            s << row[i];
            getline(s, nazov, ',');
            getline(s, nazov, ',');
            if (i > 0) {
                vystup += "|";
            }
            vystup += nazov;
        }
    }
    return vystup;
}

string Databaza::getZoznamTabuliekPouzivatelaSPristupom(const string &menoPouzivatela) {
    string vystup;
    string riadok;
    vector<string> row;
    vector<string> tabs;
    vector<string> temp;
    string word;
    int count = 0;
    string nazovTab;

    fstream fin;
    fin.open("ZoznamTabuliek.csv", ios::in);

    while(getline(fin, riadok)) {
        row.push_back(riadok);
    }

    for (int i = 0; i < row.size(); ++i) {
        count = 0;
        stringstream s;
        s << row[i];
        while (getline(s, word, ',')) {
            ++count;
            if (count == 2) {
                tabs.push_back(word);
            }
        }
    }

    fin.close();

    for (int i = 0; i < tabs.size(); ++i) {
        nazovTab = "pristupy_" + tabs[i];
        fstream fin;
        fin.open(nazovTab, ios::in);
        temp.clear();

        while(getline(fin, riadok)) {
            temp.push_back(riadok);
        }

        for (int j = 0; j < temp.size(); ++j) {
            stringstream s;
            s << temp[j];

            getline(s, word);

            if (word.find(menoPouzivatela) != std::string::npos) {
                getline(s, word);
                if (j > 0) {
                    vystup += "|";
                }
                vystup += tabs[i];
            }
        }
    }
    return vystup;
}



