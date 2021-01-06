//
// Created by Michal on 29. 12. 2020.
//

#include "Menu.h"

using namespace std;

void Menu::vyber_kli_ser() {
    int vstup = 99;
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
            spustiServer();
            break;
        case 2:
            spustiKlienta();
            break;
    };
}

void Menu::spustiServer() {
    int vstup = 99;
    Server* server = new Server(9876);
    int spusteni = 0;

    ClearScreen();
    cout << "===== Sever =====" << endl;
    cout << "Server je zapnuty!" << endl;
    cout << "1. vypnut server" << endl;

    do {
        cin >> vstup;
    } while (vstup != 1);

    vstup = 99;
    delete server;
}

void Menu::spustiKlienta() {
    Klient* klient = new Klient("localhost",9876);

    int vstup = 99;
    do {
        ClearScreen();
        cout << "===== Klient =====" << endl;
        cout << "1. vytvorit konto" << endl;
        cout << "2. prihlasit sa" << endl;
        cout << "3. ukoncit program" << endl;
        cin >> vstup;

        switch(vstup)
        {
            case 1:
                ClearScreen();
                this->prihlasenie();
                vstup = 0;
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
    int heslo;
    int vstup = 99;

    do {

        cout << "===== Registracia =====" << endl;
        cout << "Zadaj aky chces mat login:" << endl;
        cin >> login;
        cout << "Zadaj ake chces mat heslo:" << endl;
        cin >> heslo;
        cout << "Tvoj login je: " << login << " a tvoje heslo je: " << heslo << endl;
        cout << "Potvrdit ?" << endl;
        cout << "1. nie, chcem zadat znova" << endl;
        cout << "2. ano, pokracovat dalej" << endl;
        cin >> vstup;
    }
    while (vstup != 1 && vstup != 2);

    // TODO registracia

}

void Menu::prihlasenie() {
    // TODO moznost vratit sa
    string login;
    int heslo;
    int UID = -1;
    bool prihlasenie = false;
    do {
        cout << "===== Prihlasenie =====" << endl;
        cout << "Zadaj login:" << endl;
        cin >> login;
        cout << "Zadaj heslo:" << endl;
        cin >> heslo;

        //TODO poslat login na Server ak acc existuje vypitat UID a zapisat ho


        if(UID >= 0) {
            prihlasenie = true;
        }
    }
    while(prihlasenie); // TODO ak je prihlasenie prejde moze ist dalej

    if(UID >= 0 ){
        user = new User(login, to_string(heslo), UID);
    }

}

void Menu::ClearScreen() {
    cout << string( 100, '\n' );
}

void Menu::vytvorTab() {
    string nazovTabulky;
    string nazvyStlpcov;
    string typStlpcu;
    int pocetStlpcov;

    cout << "===== Vytvorenie tabulky =====" << endl;
    cout << "Zadaj nazov tabulky." << endl;
    cin >> nazovTabulky;
    cout << "Zadaj pocet stlpcov tabulky" << endl;
    cin >> pocetStlpcov;

    if(pocetStlpcov > 0) {
        for(int i = 0; i < pocetStlpcov; i++){
            string nazov;
            int typ = 99;
            cout << "Ako sa ma volat prvy stlpec? " << endl;
            cin >> nazov;
            // TODO while
            do {
                if(typ != 99)
                {
                    cout << "Zly vstup zadaj znovu" << endl;
                }
                cout << "Akeho ma byt typu" << endl;
                cout << "0. int" << endl;
                cout << "1. double" << endl;
                cout << "2. bool" << endl;
                cout << "3. string"<< endl;
                cout << "4. date" << endl;
                cin >> typ;
            } while (typ != 0 && typ != 1 && typ != 2 && typ != 3 && typ != 4);

            if(i > 0) {
                nazvyStlpcov += ",";
            }

            switch(typ){
                case 0:
                    nazvyStlpcov += "int";
                    break;
                case 1:
                    nazvyStlpcov += "double";
                    break;
                case 2:
                    nazvyStlpcov += "bool";
                    break;
                case 3:
                    nazvyStlpcov += "string";
                    break;
                case 4:
                    nazvyStlpcov += "date";
                    break;

            }
        }
    }

    // TODO prekladac vytvorTab
}

void Menu::vypisVytvoreneTab() {
    int vstup = 99;
    do {
        vstup =99;
        cout << "===== Vytvoril si tieto tabulky ======" << endl;
        // TODO Prekladac vypis vytvorene Tab
        do {
            cout << "1. pridat niekomu pristupove prava k tabulke" << endl;
            cout << "2. vyber tabulku" << endl;
            cout << "3. zmaz tabulku" << endl;
            cout << "4. exit" << endl;
            cin >> vstup;

        } while( vstup != 1 && vstup != 2 && vstup != 3 && vstup != 4);

        // TODO dorobit case
        switch(vstup) {
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
        }
    } while (vstup != 4);

}

void Menu::vypisPristupneTab() {
    int vstup = 99;
    do {
        vstup =99;
        cout << "===== Mas pristup k tymto tabulkam ======" << endl;
        // TODO Prekladac vypis vytvorene Tab
        do {
            cout << "1. vyber tabulku" << endl;
            cout << "2. exit" << endl;
            cin >> vstup;

        } while(vstup != 1 && vstup != 2);

        // TODO dorobit case
        switch(vstup) {
            case 1:

                break;
        }
    } while (vstup != 2);
}

void Menu::UpravaTab() {
    int vstup = 99;
    do {
        vstup =99;
        cout << "===== Mas pristup k tymto tabulkam ======" << endl;
        // TODO Prekladac vypis vytvorene Tab
        do {
            cout << "1. Pridat zaznam" << endl;
            cout << "2. Aktualizovat zaznam" << endl;
            cout << "3. Zmazat zaznam" << endl;
            cout << "4. Vypisat zaznamy v neutriedenom poradi" << endl;
            cout << "5. Vypisat zaznamy v utriedenom poradi podla zvoleneho stlpca" << endl;
            cout << "6. exit" << endl;
            cin >> vstup;

        } while(vstup != 1 && vstup != 2 && vstup != 3 && vstup != 4 && vstup != 5 && vstup != 6);

        // TODO dorobit case
        switch(vstup) {
            case 1:
                // TODO pridat zaznam
                break;
            case 2:
                // TODO Aktualizovat zaznam
                break;
            case 3:
                // TODO Zmazat zaznam
                break;
            case 4:
                // TODO Vypisat zaznamy v neutriedenom poradi
                break;
            case 5:
                // TODO Vypisat zaznamy v utriedenom poradi podla zvoleneho stlpca
                break;
        }
    } while (vstup != 6);
}













