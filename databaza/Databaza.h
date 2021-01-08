//
// Created by Pocitac on 2.1.2021.
//

#ifndef SKUSKA_DATA_H
#define SKUSKA_DATA_H

#endif //SKUSKA_DATA_H
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <sstream>
#include <vector>

using namespace std;

class Databaza{
public:
    Databaza();
    ~Databaza();
    bool vytvorTab(const string& nazovTabulky,const string& menoPouzivatela, int pocetStlpcov, const string& nazvyStlcov, const string& datoveTypy);
    bool zrusTab(const string& nazovTabulky);
    bool exists (const string& nazovTabulky);
    int jeUzivatel(const string& udaje);
    void zapisPouzivatela (const string& udaje);
    bool nastavPristup( const string & nazovTabulky,const string &menoPouzivatela, const string &dataPristupov);
    bool aktualizujVsetkyPristupy( const string & nazovTabulky,const string &menoPouzivatela, const string &dataPristupov);
    string getPristup(const string &nazovTabulky, const string &menoPouzivatela);
    string getZoznamTabuliekPouzivatela(const string &menoPouzivatela);
    string getZoznamTabuliekPouzivatelaSPristupom(const string &menoPouzivatela);


private:

};