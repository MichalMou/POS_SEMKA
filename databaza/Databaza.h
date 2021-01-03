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

using namespace std;

class Databaza{
public:
    Databaza();
    ~Databaza();
    bool vytvorTab(const string& name);
    bool zrusTab(const string& name);
    bool exists (const string& name);

private:
};