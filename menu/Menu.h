//
// Created by Michal on 29. 12. 2020.
//

#ifndef UNTITLED6_MENU_H
#define UNTITLED6_MENU_H

#include <iostream>
#include <stdio.h>

using namespace std;

class Menu {
public:
    void start_menu();
    void vyber_cli_ser();
    void prihlasenie();
    void registracia();
    static void ClearScreen(){
        cout << string( 100, '\n' );
    }
private:
    int vstup;

};


#endif //UNTITLED6_MENU_H
