//
// Created by Michal on 1. 1. 2021.
//

#include "User.h"

User::User() {
    meno = "";
    heslo = "";
    menoUpravovanejTab = "";
    UID = 0;
}

string User::getMenoUpravovanejTab() {
    return this->menoUpravovanejTab;
}

string User::getMeno() {
    return this->meno;
}

string User::getHeslo() {
    return this->heslo;
}

int User::getUID() {
    return this->UID;
}

void User::setMenoUpravovanejTab(string parMenoTab) {
    menoUpravovanejTab = parMenoTab;
}

void User::setMeno(string parMeno) {
    meno = parMeno;
}

void User::setHeslo(string parHeslo) {
    heslo = parHeslo;
}

void User::setUID(int parUID) {
    UID = parUID;
}
