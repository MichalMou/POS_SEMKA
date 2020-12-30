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
        cout << "0. nie" << endl;
        cout << "1. ano" << endl;
        cin >> vstup;
        if (vstup == 1) {
            potvrdit = 1;
        } else {
            potvrdit = 0;
        }
    }
    while (potvrdit != 1);
    // TODO registracia

}

void Menu::prihlasenie() {
    string login;
    int heslo;
    cout << "Prihlasenie" << endl;
    cout << "Zadaj login:" << endl;
    cin >> login;
    cout << "Zadaj heslo:" << endl;
    cin >> heslo;


    // TODO vytvor konto


}

void Menu::vyber_cli_ser() {
    cout << "===== Vitaj v database programe =====" << endl;
    cout << "Chces byt:" << endl;
    cout << "1. server" << endl;
    cout << "2. klient" << endl;
    cin >> vstup;

    switch(vstup)
    {
        case 1:
            // TODO zapnuty server
            break;
        case 2:
            start_menu();
            break;
        default:
            cout << "Zadal si zly vstup, skus znova!" << endl;
            cin >> vstup;
    };
}















