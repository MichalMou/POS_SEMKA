//
// Created by Pocitac on 2.1.2021.
//

#include "Tabulka.h"

Tabulka::Tabulka() {

}

Tabulka::~Tabulka() {

}

bool Tabulka::pridajZaznam(const string& nazovTabulky, const string& data) {
    string riadok;
    string poslednyRiadok;
    stringstream temp;
    fstream fout;
    int count = 0;
    int id = 0;
    string idString;
    if(!exists(nazovTabulky)) {
        return false;
    }

    ifstream subor(nazovTabulky);

    if(subor.is_open()) {
        subor.seekg(0,std::ios_base::end);      //Start at end of file
        char ch = ' ';                        //Init ch not equal to '\n'
        while(ch != '\n'){
            subor.seekg(-2,std::ios_base::cur); //Two steps back, this means we
            //will NOT check the last character
            if((int)subor.tellg() <= 0){        //If passed the start of the file,
                subor.seekg(0);                 //this is the start of the line
                break;
            }
            subor.get(ch);                      //Check the next character
        }

        getline(subor,poslednyRiadok);

        temp.str(poslednyRiadok);
        getline(temp, idString,',');
        for (int i = 0; i < idString.length(); ++i) {
            if (isdigit(idString[i]) == false){
                count = 1;
                break;
            } else {
                count = 0;
            }
        }

        if (count == 1) {
            id = 0;
        } else {
            id = stoi(idString);
        }

        subor.close();
    }
    temp.clear();
    //Prvy riadok - meno
    getline(subor,riadok);

    //Nacita riadok s nazvami stlpcov
    getline(subor, riadok);

    //Nacita riadok s datovymi typmi
    getline(subor, riadok);

    //Zapis zaznamu do suboru
    fout.open(nazovTabulky, ios::out | ios::app);

    fout << id + 1 << "," << data << endl;

    fout.close();

    return true;
}

bool Tabulka::vymazZaznam(const string& nazovTabulky, int id) {
    fstream fin,fout;
    int zhoda = 0;
    vector<string> row;
    string line, word, meno, stlpce, typy;

    if(!exists(nazovTabulky)) {
        return false;
    }

    fin.open(nazovTabulky,ios::in);
    fout.open("new.csv",ios::out);


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
        if (id == 0) {
            zhoda = 1;
        } else {
            int roll = stoi(row[0]);
            if (roll != id) {
                if (!fin.eof()) {
                    for (int i = 0; i < row.size() - 1; ++i) {
                        fout << row[i] << ",";
                    }
                    fout << row[row.size() - 1] << endl;
                }
            } else {
                zhoda = 1;
            }
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

    remove(nazovTabulky.c_str());
    rename("new.csv", nazovTabulky.c_str());

    return true;
}

bool Tabulka::aktualizujZaznam(const string& nazovTabulky, int id, const string& nazovStlpca, const string &data) {

    fstream fin,fout;
    vector<string> row;
    vector<string> nazvyStlpcov;
    stringstream temp;
    string line, word, meno, stlpce, typy;
    int index = 0;
    int count = 0;

    if(!exists(nazovTabulky)) {
        return false;
    }

    fin.open(nazovTabulky, ios::in);
    fout.open("new.csv", ios::out);

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

        for(string &nazov : nazvyStlpcov) {
            ++count;
            if (nazov == nazovStlpca) {
                index = count - 1;
            }
        }

        if (index == 0) {
            cout << "Nespravny nazov stlpca. Skus znovu: " << endl;
        }
    }

    while(!fin.eof()) {
        row.clear();

        getline(fin, line);
        stringstream s(line);

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        int roll = stoi(row[0]);

        if (roll == id) {
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

    remove(nazovTabulky.c_str());
    rename("new.csv", nazovTabulky.c_str());
    return true;
}

string Tabulka::vypisNeutriedenejTabulky(const string& name, int vstup) {
    fstream fin;
    string riadok;
    bool hodnota = false;
    int count = 0;
    int pocetRiadkov = 0;
    string vystup;

    if(!exists(name)) {
        return "Neexistuje";
    }

    fin.open(name.c_str(), ios::in);

    while(getline(fin, riadok)) {
        ++pocetRiadkov;
    }
    fin.clear();
    fin.seekg(0);

    while (!hodnota) {
        if (vstup == 0) {
            while(!fin.eof()) {
                getline(fin, riadok);
                vystup += riadok + "|";
                hodnota = true;
            }
        } else {
            if (vstup <= pocetRiadkov - 3) {
                getline(fin, riadok);
                vystup += riadok + "|";
                getline(fin, riadok);
                vystup += riadok + "|";
                getline(fin, riadok);
                vystup += riadok + "|";

                while (count != vstup) {
                    getline(fin, riadok);
                    vystup += riadok + "|";
                    ++count;
                }
                hodnota = true;

            } else {
                cout << "Tolko zaznamov v tabulke nie je skuste znova." << endl;
            }
        }
    }
    fin.close();
    return vystup;
}

string Tabulka::vypisUtriedenejTabulky(const string& name, const string& nazovStlpca, int vstup) {
    fstream fin;
    string riadok, meno, stlpce, typy, slovo, word;
    int count = 0;
    int pocetRiadkov = 0;
    vector<string> dataZoStlpcov;
    vector<string> row;
    vector<string> nazvyStlpcov;
    vector<string> allRows;
    stringstream temp;
    int index = 0;

    if (!exists(name)) {
        return "Chyba";
    }

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

        for(string &nazov : nazvyStlpcov) {
            ++count;
            if (nazov == nazovStlpca) {
                index = count - 1;
            }
        }

        if (index == 0) {
            cout << "Nespravny nazov stlpca." << endl;
            return nullptr;
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

        sort(dataZoStlpcov.begin(), dataZoStlpcov.end(), [](const auto& lhs, const auto& rhs){
            const auto result = mismatch(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend(), [](const auto& lhs, const auto& rhs){return tolower(lhs) == tolower(rhs);});

            return result.second != rhs.cend() && (result.first == lhs.cend() || tolower(*result.first) < tolower(*result.second));
        });


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

    string vystup;

    if (vstup == 0) {
        for (int i = 0; i < n; ++i) {
            vystup += pole[i] + "|";
        }
    } else {
        if (vstup <= pocetRiadkov) {
            for (int i = 0; i < vstup; ++i) {
                vystup += pole[i] + "|";
            }
        } else {
            cout << "Tolko zaznamov v tabulke nie je skuste znova." << endl;
        }
    }

    fin.close();
    return vystup;
}

bool Tabulka::exists(const string &name) {
    ifstream f((name).c_str());
    return f.good();
}

string Tabulka::getMenoTvorcu(const string& nazovTabulky) {
    fstream fin;
    string riadok;

    fin.open(nazovTabulky, ios::in);

    getline(fin, riadok);

    return riadok;
}

string Tabulka::getNazvyStlpcov(const string &nazovTabulky) {
    fstream fin;
    string riadok;

    fin.open(nazovTabulky, ios::in);

    getline(fin, riadok);
    getline(fin, riadok);

    return riadok;
}

string Tabulka::getDatTypyStlpcov(const string &nazovTabulky) {
    fstream fin;
    string riadok;

    fin.open(nazovTabulky, ios::in);

    getline(fin, riadok);
    getline(fin, riadok);
    getline(fin, riadok);

    return riadok;
}
