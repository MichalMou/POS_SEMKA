//
// Created by Pocitac on 2.1.2021.
//

#ifndef SKUSKA_TABULKA_H
#define SKUSKA_TABULKA_H

#endif //SKUSKA_TABULKA_H

#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Tabulka {
public:
    Tabulka();
    ~Tabulka();

    bool pridajZaznam(const string& nazovTabulky, const string& data);
    bool vymazZaznam(const string& nazovTabulky, int id);
    bool aktualizujZaznam(const string& nazovTabulky, int id, const string& nazovStlpca, const string &data);
    string vypisNeutriedenejTabulky(const string& name);
    string vypisUtriedenejTabulky(const string& name, const string& nazovStlpca);
    bool exists (const string& name);
    string getMenoTvorcu(const string& nazovTabulky);
    string getNazvyStlpcov(const string& nazovTabulky);
    string getDatTypyStlpcov(const string& nazovTabulky);
private:

};