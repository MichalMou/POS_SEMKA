//
// Created by Pocitac on 2.1.2021.
//

#include "Tabulka.h"


Tabulka::Tabulka() {

}

Tabulka::~Tabulka() {

}

bool Tabulka::pridajZaznam(const string& name) {
    // TODO nejake kontroly ohladom suborov + vypis k ostatnym ak sa nenajdu dany zaznam
    // TODO vsetky zaznamy musia byt NOT NULL + aj v ostatnych metódach

    string riadok;
    int count = 0;
    stringstream temp;
    vector<string> nazvyStlpcov;
    vector<string> datTypy;
    fstream fout;
    string vstup;
    bool spravne;
    ifstream subor(name);

    //Cyklus na spocitanie riadkov v tabulke
    while(getline(subor,riadok)) {
        ++count;
    }
    subor.clear();
    subor.seekg(0);

    //Prvy riadok vypise meno
    getline(subor,riadok);
    cout << riadok << endl;

    //Nacita riadok s nazvami stlpcov
    getline(subor, riadok);
    temp.str(riadok);
    while  (getline(temp, riadok,',')){
        nazvyStlpcov.push_back(riadok);
    }

    temp.clear();

    //Nacita riadok s datovymi typmi
    getline(subor, riadok);
    temp.str(riadok);
    while  (getline(temp, riadok,',')){
        datTypy.push_back(riadok);
    }

    //Zapis zaznamu do suboru
    fout.open(name, ios::out | ios::app);

    fout << (count - 2) << ",";

    for (int i = 1; i < nazvyStlpcov.size(); ++i) {
        spravne = false;

        while (!spravne) {
            cout << nazvyStlpcov[i] << ": " << endl;
            cin >> vstup;

            if (datTypy[i] == "int") {
                if (i+1 == nazvyStlpcov.size()) {
                    fout << vstup << endl;
                    spravne = true;
                } else {
                    fout << vstup << ",";
                    spravne = true;
                }
            } else if (datTypy[i] == "string") {
                if (i+1 == nazvyStlpcov.size()) {
                    fout << vstup << endl;
                    spravne = true;
                } else {
                    fout << vstup << ",";
                    spravne = true;
                }
            } else if (datTypy[i] == "double") {
                if (i+1 == nazvyStlpcov.size()) {
                    fout << vstup << endl;
                    spravne = true;
                } else {
                    fout << vstup << ",";
                    spravne = true;
                }
            } else if (datTypy[i] == "date") {
                if (i+1 == nazvyStlpcov.size()) {
                    fout << vstup << endl;
                    spravne = true;
                } else {
                    fout << vstup << ",";
                    spravne = true;
                }
            } else if (datTypy[i] == "boolean") {
                if (i+1 == nazvyStlpcov.size()) {
                    fout << vstup << endl;
                    spravne = true;
                } else {
                    fout << vstup << ",";
                    spravne = true;
                }
            }
        }
    }
    return true;
}

bool Tabulka::vymazZaznam(const string& name) {
    // TODO nejake kontroly ohladom suborov + vypis k ostatnym ak sa nenajdu dany zaznam
    // TODO volba vymazat 1 alebo vsetky zaznamy + dorobit vymazanie vsetkych

    fstream fin,fout;
    int rowNumber;
    int zhoda = 0;
    vector<string> row;
    string line, word, meno, stlpce, typy;

    fin.open(name,ios::in);
    fout.open("new.csv",ios::out);

    cout << "Zadajte ID riadku pre zmazanie: " << endl;
    cin >> rowNumber;

    getline(fin,meno);

    getline(fin,stlpce);

    getline(fin,typy);

    fout << meno << endl;
    fout << stlpce << endl;
    fout << typy << endl;

    while(!fin.eof()) {
        row.clear();

        getline(fin,line);

        stringstream s(line);

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        int roll = stoi(row[0]);

        if (roll != rowNumber) {
            if (!fin.eof()) {
                for (int i = 0; i < row.size() - 1; ++i) {
                    fout << row[i] << ",";
                }
                fout << row[row.size() - 1] << endl;
            }
        } else {
            zhoda = 1;
        }
        if (fin.eof()) {
            break;
        }
    }
    if (zhoda == 1) {
        cout << "Zaznam uspesne zmazany" << endl;
    } else {
        cout << "Taky zaznam neexistuje" << endl;
    }

    fin.close();
    fout.close();

    remove(name.c_str());
    rename("new.csv", name.c_str());

    return true;
}

bool Tabulka::aktualizujZaznam(const string& name) {
    // TODO nejake kontroly ohladom suborov + vypis k ostatnym ak sa nenajdu dany zaznam

    fstream fin,fout;
    int rowNumber;
    vector<string> row;
    vector<string> nazvyStlpcov;
    stringstream temp;
    string line, word, meno, stlpce, typy;
    int index = 0;
    string inIndex;
    int count = 0;
    string data;

    fin.open(name, ios::in);

    fout.open("new.csv", ios::out);

    cout << "Zadajte ID riadku ktory chcete zmenit: " << endl;
    cin >> rowNumber;

    getline(fin,meno);
    fout << meno << endl;
    getline(fin,stlpce);
    fout << stlpce << endl;
    temp.str(stlpce);

    while(getline(temp, stlpce,',')) {
        nazvyStlpcov.push_back(stlpce);
    }

    getline(fin,typy);
    fout << typy << endl;

    while(index == 0) {
        cout << "Zadajte nazov stlpca ktory chcete zmenit: " << endl;
        cin >> inIndex;

        for(string &nazov : nazvyStlpcov) {
            ++count;
            if (nazov == inIndex) {
                index = count - 1;
            }
        }

        if (index == 0) {
            cout << "Nespravny nazov stlpca. Skus znovu: " << endl;
        }
    }

    cout << "Zadajte data pre zmenu: " << endl;
    cin >> data;

    while(!fin.eof()) {
        row.clear();

        getline(fin, line);
        stringstream s(line);

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        int roll = stoi(row[0]);

        if (roll == rowNumber) {
            stringstream zmena;

            zmena << data;
            row[index] = zmena.str();
            if (!fin.eof()) {
                for (int i = 0; i < row.size() - 1; ++i) {
                    fout << row[i] << ",";
                }
                fout << row[row.size() - 1] << endl;
            }
        } else {
            if (!fin.eof()) {
                for (int i = 0; i < row.size() - 1; ++i) {
                    fout << row[i] << ",";
                }
                fout << row[row.size() - 1] << endl;
            }
        }
        if (fin.eof()) {
            break;
        }
    }
    fin.close();
    fout.close();

    remove(name.c_str());
    rename("new.csv", name.c_str());
    return true;
}

void Tabulka::vypisNeutriedenejTabulky(const string& name) {
    fstream fin;
    string riadok;
    bool hodnota = false;
    int vstup;
    int count = 0;
    int pocetRiadkov = 0;

    fin.open(name.c_str(), ios::in);

    while(getline(fin, riadok)) {
        ++pocetRiadkov;
    }
    fin.clear();
    fin.seekg(0);

    while (!hodnota) {
        cout << "Kolko zaznamov chcete vypisat ?   {0 - znamena vsetky hodnoty} ";
        cin >> vstup;

        if (vstup == 0) {
            while(!fin.eof()) {
                getline(fin, riadok);
                cout << riadok << endl;
                hodnota = true;
            }
        } else {
            if (vstup <= pocetRiadkov - 3) {
                getline(fin, riadok);
                cout << riadok << endl;
                getline(fin, riadok);
                cout << riadok << endl;
                getline(fin, riadok);
                cout << riadok << endl;

                while (count != vstup) {
                    getline(fin, riadok);
                    cout << riadok << endl;
                    ++count;
                }
                hodnota = true;

            } else {
                cout << "Tolko zaznamov v tabulke nie je" << endl;
            }
        }
    }
    fin.close();
}

void Tabulka::vypisUtriedenejTabulky(const string& name) {
    fstream fin;
    string riadok, meno, stlpce, typy, slovo, word;
    bool hodnota = false;
    int count = 0;
    int pocetRiadkov = 0;
    vector<string> dataZoStlpcov;
    vector<string> row;
    vector<string> nazvyStlpcov;
    vector<string> allRows;
    stringstream temp;
    int index = 0;
    string inIndex;


    fin.open(name.c_str(), ios::in);

    while(getline(fin, riadok)) {
        ++pocetRiadkov;
    }
    fin.clear();
    fin.seekg(0);

    getline(fin, meno);

    getline(fin, stlpce);

    temp.str(stlpce);
    while(getline(temp, word,',')) {
        nazvyStlpcov.push_back(word);
    }
    getline(fin, typy);


    while(index == 0) {
        cout << "Zadajte nazov stlpca ktory chcete zmenit: " << endl;
        cin >> inIndex;

        for(string &nazov : nazvyStlpcov) {
            ++count;
            if (nazov == inIndex) {
                index = count - 1;
                //cout << "index: " << index << endl;
            }
        }

        if (index == 0) {
            cout << "Nespravny nazov stlpca. Skus znovu: " << endl;
        }
    }

    while(!fin.eof()) {
        row.clear();

        getline(fin,riadok, '\n');
        allRows.push_back(riadok);

        stringstream s(riadok);

        while (getline(s, slovo, ',')) {
            row.push_back(slovo);
        }

        for(int i = 0; i < row.size(); ++i) {
            if (i == index) {
                dataZoStlpcov.push_back(row[i]);
            }
        }

        sort(dataZoStlpcov.begin(), dataZoStlpcov.end());


        if (fin.eof()) {
            break;
        }
    }

    allRows.erase(allRows.end());

    string pole[allRows.size()];

    int n = sizeof(pole) / sizeof(pole[0]);

    for (int i = 0; i < allRows.size(); ++i) {
        for (int j = 0; j < dataZoStlpcov.size(); ++j) {
            if (allRows[i].find(dataZoStlpcov[j]) != std::string::npos) {
                pole[j] = allRows[i];
            }
        }
    }

    cout << meno << endl;
    cout << stlpce << endl;
    cout << typy << endl;

    for (int i = 0; i < n; ++i) {
        cout << pole[i] << endl;
    }

    fin.close();

}

void Tabulka::nastavPristup() {

}