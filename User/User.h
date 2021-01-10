//
// Created by Michal on 1. 1. 2021.
//

#ifndef UNTITLED6_USER_H
#define UNTITLED6_USER_H

#include <string>

using namespace std;

class User {
public:
    User();
    string getMenoUpravovanejTab();
    string getMeno();
    string getHeslo();
    int getUID();

    void setMenoUpravovanejTab(string parMenoTab);
    void setMeno(string parMeno);
    void setHeslo(string parHeslo);
    void setUID(int parUID);

private:
    string menoUpravovanejTab;
    string meno;
    string heslo;
    int UID;
};


#endif //UNTITLED6_USER_H
