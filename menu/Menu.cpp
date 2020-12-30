//
// Created by Michal on 29. 12. 2020.
//

#include "Menu.h"

using namespace std;

void Menu::start_menu() {
    do {
        vstup = 99;
        ClearScreen();
        cout << "1. vytvorit konto" << endl;
        cout << "2. prihlasit sa" << endl;
        cout << "3. ukoncit program" << endl;
        cin >> vstup;

        switch(vstup)
        {
            case 1:
                ClearScreen();
                this->prihlasenie();
                break;
            case 2:
                ClearScreen();
                this->registracia();
                break;
            case 3:
                ClearScreen();
                vstup = 0;
                break;
        }
    }
    while(vstup != 0);
}

void Menu::registracia() {
    string login;
    int heslo, potvrdit;

    do {
        cout << "Registracia" << endl;
        cout << "Zadaj aky chces mat login:" << endl;
        cin >> login;
        cout << "Zadaj ake chces mat heslo:" << endl;
        cin >> heslo;
        cout << "Tvoj login je: " << login << " a tvoje heslo je: " << heslo << endl;
        cout << "Potvrdit ?" << endl;
        cout << "0. nie, chcem zadat znova" << endl;
        cout << "1. ano, pokracovat dalej" << endl;
        cin >> vstup;
    }
    while (vstup != 1 && vstup != 0);
    // TODO registracia

}

void Menu::prihlasenie() {
    string login;
    int heslo;
    do {

    }
    cout << "Prihlasenie" << endl;
    cout << "Zadaj login:" << endl;
    cin >> login;
    cout << "Zadaj heslo:" << endl;
    cin >> heslo;


    // TODO vytvor konto


}

void Menu::vyber_cli_ser() {
    do {
        ClearScreen();
        cout << "===== Vitaj v database programe =====" << endl;
        cout << "Chces byt:" << endl;
        cout << "1. server" << endl;
        cout << "2. klient" << endl;
        cin >> vstup;
    }
    while (vstup != 1 && vstup != 2);

    switch(vstup)
    {
        case 1:
            // TODO zapnuty server
            break;
        case 2:
            start_menu();
            break;
    };
}















