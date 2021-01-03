//
// Created by Pocitac on 2.1.2021.
//


#include "Databaza.h"

Databaza::Databaza() {

}

Databaza::~Databaza() {

}

bool Databaza::vytvorTab(const string& name) {
    // TODO dorobit pri vytvarani aby sa vytvorila aj tabulka pristupo
    // TODO dorobit zapis mena tvorcu tabulky + jeho pristupy na 1

    int pocetStlpcov;
    string nazovStlpca;
    int datTypStlpca;
    bool spravne = false;


    if (exists(name)) {
        cout << "tabulka existuje" << endl;
        return false;
    }

    cout << "Prvy stlpec je vzdy ID." << endl;
    cout << "Minimalny pocet stlpcov je 2" << endl;
    cout << "Zadajte pocet stlpcov:" << endl;

    cin >> pocetStlpcov;

    if (pocetStlpcov > 1) {

        fstream fout;
        fout.open(name, ios::out | ios::app);
        fout << "Tvorca: Meno..." << endl;
        fout << "ID,";
        for (int i = 1; i < pocetStlpcov; ++i) {
            cout << "Zadajte nazov stlpca: ";
            cin >> nazovStlpca;
            if (i + 1 == pocetStlpcov) {
                fout << nazovStlpca << endl;
            } else {
                fout << nazovStlpca << ",";
            }
        }
        fout << "int,";
        for (int i = 1; i < pocetStlpcov; ++i) {
            spravne = false;
            cout << "Zadajte datovy typ stlpcov: {0 - INT, 1 - STRING, 2 - DOUBLE, 3 - DATE, 4 - BOOLEAN}";
            while(!spravne) {
                cin >> datTypStlpca;
                switch (datTypStlpca) {
                    case 0:
                        if (i + 1 == pocetStlpcov) {
                            fout << "int" << endl;
                        } else {
                            fout << "int,";
                        }

                        spravne = true;
                        break;
                    case 1:
                        if (i + 1 == pocetStlpcov) {
                            fout << "string" << endl;
                        } else {
                            fout << "string,";
                        }

                        spravne = true;
                        break;
                    case 2:
                        if (i + 1 == pocetStlpcov) {
                            fout << "double" << endl;
                        } else {
                            fout << "double,";
                        }

                        spravne = true;
                        break;
                    case 3:
                        if (i + 1 == pocetStlpcov) {
                            fout << "date" << endl;
                        } else {
                            fout << "date,";
                        }

                        spravne = true;
                        break;
                    case 4:
                        if (i + 1 == pocetStlpcov) {
                            fout << "boolean" << endl;
                        } else {
                            fout << "boolean,";
                        }

                        spravne = true;
                        break;
                    default:
                        cout << "Nespravna moznost. Skus znovu" << endl;
                }
            }
        }
        fout.close();
        cout << "tabulka uspesne vytvorena" << endl;

        return true;
    } else {
        cout << "Minimalny pocet stlpcov je 2" << endl;
        return false;
    }
}

bool Databaza::zrusTab(const std::string& name) {
    if (exists(name)) {
        unlink((name).c_str());
        cout << "tabulka vymazana" << endl;
        return true;
    }

    cout << "tabulka neexistuje" << endl;
    return false;
}

bool Databaza::exists(const string& name) {
        ifstream f((name).c_str());
        return f.good();
}
