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

    bool pridajZaznam(const string& name);
    bool vymazZaznam(const string& name);
    bool aktualizujZaznam(const string& name);
    void vypisNeutriedenejTabulky(const string& name);
    void vypisUtriedenejTabulky(const string& name);
    void nastavPristup();

    // TODO vypisUtriedenu/Neutriedenu tabulku
    // TODO hladajZaznam()
    // TODO pri nastavovani pristupu sa posiela UID

private:

};