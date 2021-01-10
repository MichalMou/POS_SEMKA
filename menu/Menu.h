//
// Created by Michal on 29. 12. 2020.
//

#ifndef UNTITLED6_MENU_H
#define UNTITLED6_MENU_H

#include <iostream>
#include <stdio.h>
#include "../server/Server.h"
#include "../klient/klient.h"
#include "../User/User.h"
#include "../klient/PrekladacKlient.h"

using namespace std;

class Menu {
public:
    void vyber_kli_ser();
    void spustiServer();
    void spustiKlienta();

    void prihlasenie();
    void registracia();

    void prihMenu();

    void vypisVytvoreneTab();
    void vypisPristupneTab();

    void vytvorTab();
    void UpravaTab();

    bool jeCislo(string cislo);

private:
    User* user;
    PrekladacKlient* prekladacKlient;

};


#endif //UNTITLED6_MENU_H
