//
// Created by Michal on 29. 12. 2020.
//

#include "Menu.h"

using namespace std;

void Menu::vyber_kli_ser() {
    int vstup = 99;
    do {
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
            cout << "koniec ?" << endl;
            break;
        case 2:
            spustiKlienta();
            break;
    };
}

void Menu::spustiServer() {
    int vstup = 99;
    Server* server = new Server(19875);
    int spusteni = 0;

    cout << "===== Sever =====" << endl;
    cout << "Server je zapnuty!" << endl;
    cout << "1. vypnut server" << endl;

    do {
        cin >> vstup;
    } while (vstup != 1);

    server->setKoniec(true);

    delete server;
}

void Menu::spustiKlienta() {
    Klient* klient = new Klient("localhost",19875);
    user = new User();
    prekladacKlient  = new PrekladacKlient(user, klient);


    int vstup = 99;
    do {
        cout << "===== Klient =====" << endl;
        cout << "1. vytvorit konto" << endl;
        cout << "2. prihlasit sa" << endl;
        cout << "3. ukoncit program" << endl;
        cin >> vstup;

        switch(vstup)
        {
            case 1:
                this->registracia();
                break;
            case 2:
                this->prihlasenie();
                break;
            case 3:
                vstup = 0;
                klient->ukonci();
                break;
        }
    }
    while(vstup != 0);

    delete klient;
    delete prekladacKlient;
    delete user;
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

    cout << prekladacKlient->registruj(login,to_string(heslo)) << endl;

}

void Menu::prihlasenie() {
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

        UID = stoi(prekladacKlient->prihlas(login,to_string(heslo)));
    }
    while(UID < 0);

    user->setMeno(login);
    user->setUID(UID);
    user->setHeslo(to_string(heslo));

    prihMenu();

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
        for(int i = 0; i < pocetStlpcov ; i++){
            string nazov;
            int typ = 99;

            cout << "Ako sa ma volat stlpec? " << endl;
            cin >> nazov;
            if(i > 0) {
                nazvyStlpcov += "|";
            }
            nazvyStlpcov += nazov;

            cout << "Akeho ma byt typu" << endl;
            cout << "0. int" << endl;
            cout << "1. double" << endl;
            cout << "2. bool" << endl;
            cout << "3. string"<< endl;
            cout << "4. date" << endl;
            do {
                cin >> typ;
                if(typ != 0 && typ != 1 && typ != 2 && typ != 3 && typ != 4)
                {
                    cout << "Zly vstup zadaj znovu" << endl;
                }
            } while (typ != 0 && typ != 1 && typ != 2 && typ != 3 && typ != 4);

            if(i > 0) {
                typStlpcu += "|";
            }

            switch(typ){
                case 0:
                    typStlpcu += "int";
                    break;
                case 1:
                    typStlpcu += "double";
                    break;
                case 2:
                    typStlpcu += "bool";
                    break;
                case 3:
                    typStlpcu += "string";
                    break;
                case 4:
                    typStlpcu += "date";
                    break;

            }
        }
    }
    if(prekladacKlient->vytvorTab(nazovTabulky,typStlpcu,nazvyStlpcov,pocetStlpcov + 1)) {
        cout << "Tabulka uspesne vytvorena." << endl;
    } else {
        cout << "Tabulka sa nemohla vytvorit, nieco sa pokazilo." << endl;
    }

}

void Menu::vypisVytvoreneTab() {
    string menoPP, vsetkyPrava, vymazTabMeno, menoTab;
    int pravo = 99;
    int vstup = 99;
    do {
        vstup =99;
        cout << "===== Vytvoril si tieto tabulky ======" << endl;
        string tabulky = prekladacKlient->vytvorene_Tab(user->getMeno());

        // cout << " tabulky v riadku" << tabulky << endl;

        vector<string> tabulkyRiadky;
        stringstream ss(tabulky);
        while (ss.good()) {
            string substr;
            getline(ss, substr, '|');
            tabulkyRiadky.push_back(substr);
        }

        for (int i = 0; i < tabulkyRiadky.size(); i++) {
            cout << tabulkyRiadky[i] << endl;
        }
        cout << "-----" << endl;

        do {
            vstup = 99;
            cout << "1. pridat niekomu pristupove prava k tabulke" << endl;
            cout << "2. vyber tabulku" << endl;
            cout << "3. zmaz tabulku" << endl;
            cout << "4. exit" << endl;

            cin >> vstup;
        } while (vstup != 1 && vstup != 2 && vstup != 3 && vstup != 4);

        switch(vstup) {
            case 1:

                cout << "Zadaj meno tabulky: " << endl;
                cin >> menoTab;

                cout << "Zadaj login uzivatela komu chces pridat prava:" << endl;
                cin >> menoPP;

                do {
                    cout << "Chces pridat pravo pridavat zaznamy?" << endl;
                    cout << "1. ano" << endl;
                    cout << "2. nie" << endl;
                    cin >> pravo;

                    if(pravo == 1){
                        vsetkyPrava += "1*";
                    } else if (pravo == 2) {
                        vsetkyPrava += "0*";
                    }
                } while (pravo != 1 && pravo != 2);
                pravo = 99;

                do {
                    cout << "Chces pridat pravo aktualizovat zaznamy?" << endl;
                    cout << "1. ano" << endl;
                    cout << "2. nie" << endl;
                    cin >> pravo;

                    if(pravo == 1){
                        vsetkyPrava += "1*";
                    } else if (pravo == 2) {
                        vsetkyPrava += "0*";
                    }
                } while (pravo != 1 && pravo != 2);
                pravo = 99;

                do {
                    cout << "Chces pridat pravo mazat zaznamy?" << endl;
                    cout << "1. ano" << endl;
                    cout << "2. nie" << endl;
                    cin >> pravo;

                    if(pravo == 1){
                        vsetkyPrava += "1*";
                    } else if (pravo == 2) {
                        vsetkyPrava += "0*";
                    }
                } while (pravo != 1 && pravo != 2);
                pravo = 99;

                do {
                    cout << "Chces pridat pravo vypisat zaznamy?" << endl;
                    cout << "1. ano" << endl;
                    cout << "2. nie" << endl;
                    cin >> pravo;

                    if(pravo == 1){
                        vsetkyPrava += "1";
                    } else if (pravo == 2) {
                        vsetkyPrava += "0";
                    }
                } while (pravo != 1 && pravo != 2);
                prekladacKlient->pridajPristupovePrava(menoPP, vsetkyPrava, menoTab);
                break;
            case 2: {
                string menoTab;
                cout << "Ktoru tabulku chces upravit?" << endl;
                cin >> menoTab;

                user->setMenoUpravovanejTab(menoTab);
                UpravaTab();
                user->setMenoUpravovanejTab("");
                break;
            }

            case 3:
                cout << "Ktoru tabulku chces vymazat?" << endl;
                cin >> vymazTabMeno;
                if(prekladacKlient->zmazTab(vymazTabMeno, user->getMeno())){
                    cout << "Tabulka uspesne vymazana." << endl;
                } else {
                    cout << "Error, chyba vo vymazani tabulky, nezadal si spravny nazov" << endl;
                }
                break;
        }
    } while (vstup != 4);

}

void Menu::vypisPristupneTab() {
    int vstup = 99;
    do {
        vstup =99;
        cout << "===== Mas pristup k tymto tabulkam ======" << endl;
        string tabulky = prekladacKlient->pristupene_Tab(user->getMeno());
        vector<string> tabulkyRiadky;

        stringstream ss(tabulky);
        while (ss.good()) {
            string substr;
            getline(ss, substr, '|');
            tabulkyRiadky.push_back(substr);
        }

        for (int i = 0; i < tabulkyRiadky.size(); i++) {
            cout << tabulkyRiadky[i] << endl;
        }
        cout << "-----" << endl;

        do {
            cout << endl;
            cout << "1. vyber tabulku" << endl;
            cout << "2. exit" << endl;
            cin >> vstup;

        } while(vstup != 1 && vstup != 2);

        switch(vstup) {
            case 1:
                string nazovTab;
                cout << endl;

                cout << "Zadaj nazov tabulky na upravovanie." << endl;
                cin >> nazovTab;
                user->setMenoUpravovanejTab(nazovTab);
                UpravaTab();
                user->setMenoUpravovanejTab("");
                break;
        }
    } while (vstup != 2);
}

void Menu::UpravaTab() {
    int vstup = 99;
    do {
        vstup = 99;
        do {
            cout << endl;

            cout << "1. Pridat zaznam" << endl;
            cout << "2. Aktualizovat zaznam" << endl;
            cout << "3. Zmazat zaznam" << endl;
            cout << "4. Vypisat zaznamy v neutriedenom poradi" << endl;
            cout << "5. Vypisat zaznamy v utriedenom poradi podla zvoleneho stlpca" << endl;
            cout << "6. exit" << endl;
            cin >> vstup;

        } while(vstup != 1 && vstup != 2 && vstup != 3 && vstup != 4 && vstup != 5 && vstup != 6);

        switch(vstup) {
            case 1: {


                string zaznam, menaTab, typTab;
                vector<string> menaStlpcov, typyStlpcov;
                menaTab = prekladacKlient->getMenaTabulky();
                typTab = prekladacKlient->getTypyTabulky();

                stringstream ss(menaTab);
                while (ss.good()) {
                    string substr;
                    getline(ss, substr, ',');
                    menaStlpcov.push_back(substr);
                }

                stringstream ssTypy(typTab);
                while (ssTypy.good()) {
                    string substr;
                    getline(ssTypy, substr, ',');
                    typyStlpcov.push_back(substr);
                }

                int stlpce = typyStlpcov.size();

                for (int i = 1; i < stlpce; i++) {
                    string hodnota;
                    cout << "Zadaj hodnotu pre " << menaStlpcov[i] << " typu " << typyStlpcov[i] << endl;
                    if (typyStlpcov[i] == "int") {
                        cin >> hodnota;

                    } else if (typyStlpcov[i] == "double") {
                        cin >> hodnota;

                    } else if (typyStlpcov[i] == "string") {
                        cin >> hodnota;

                    } else if (typyStlpcov[i] == "date") {
                        string den, mesiac, rok;

                            cout << "Zadaj den, cislom." << endl;
                            cin >> den;

                            cout << "Zadaj mesiac, cislom." << endl;
                            cin >> mesiac;
                            cout << "Zadaj rok, cislo." << endl;
                            cin >> rok;

                        hodnota = den + "." + mesiac + "." + rok;

                    } else if (typyStlpcov[i] == "bool") {
                        int vstupBool;
                        do {
                            cout << "Zadaj hodnotu: " << endl;
                            cout << "1.true" << endl;
                            cout << "2.false" << endl;
                            cin >> vstupBool;
                        } while (vstupBool != 1 && vstupBool != 2);
                        if (vstupBool == 1) {
                            hodnota = "true";
                        } else {
                            hodnota = "false";
                        }
                    }

                    if (i > 1) {
                        zaznam += ",";
                    }
                    zaznam += hodnota;
                }
                cout << "zaznam na zapis:" << zaznam << endl;
                prekladacKlient->pridajZaznam(zaznam);
                break;
            }
            case 2: {
                string upravenyStlpec, upravenaHodnota;
                int UID;

                cout << "Zvol ID riadku ktorý chceš aktualizovat" << endl;
                cin >> UID;

                cout << prekladacKlient->getMenaTabulky() << endl;
                cout << "Zvol ktory stlpec ches upravit" << endl;
                cin >> upravenyStlpec;

                cout << "Zadaj Upravenu hodnotu." << endl;
                cin >> upravenaHodnota;

                if (!prekladacKlient->aktualizovatZaznam(upravenaHodnota, UID, upravenyStlpec)) {
                    cout << "Hodnota uspesne upravena." << endl;
                } else {
                    cout << "Hodnotu sa nepodarilo upravit." << endl;
                }
                break;
            }

            case 3: {
                int UID;
                cout << "Zadaj cislom ktory zaznam chces upravit." << endl;
                cin >> UID;


                if (!prekladacKlient->zmazatZaznam(UID)) {
                    cout << "Zaznam uspesne zmazany." << endl;
                } else {
                    cout << "Zaznam sa nepodarilo zmazat." << endl;
                }
                break;
            }

            case 4: {
                string zaznamy = prekladacKlient->vypisatZaznamiNeutriedene();

                vector<string> rozsekaneZaznamy;
                stringstream ss(zaznamy);
                while (ss.good()) {
                    string substr;
                    getline(ss, substr, '|');
                    rozsekaneZaznamy.push_back(substr);
                }

                for (int i = 0; i < rozsekaneZaznamy.size(); i++) {
                    cout << rozsekaneZaznamy[i] << endl;
                }

                break;
            }

            case 5: {
                int cisloStlpca;
                cout << "Zadaj cislo stlpca podla ktoreho chces utriedit" << endl;
                cin >> cisloStlpca;
                string zaznamy = prekladacKlient->vypisatZaznamiUtriedene(cisloStlpca);

                vector<string> rozsekaneZaznamy;
                stringstream ss(zaznamy);
                while (ss.good()) {
                    string substr;
                    getline(ss, substr, '|');
                    rozsekaneZaznamy.push_back(substr);
                }

                for (int i = 0; i < rozsekaneZaznamy.size(); i++) {
                    cout << rozsekaneZaznamy[i] << endl;
                }

                break;
            }
        }

    } while (vstup != 6);
}

void Menu::prihMenu() {
    int vstup = 99;
    do {
        vstup = 99;
        cout << "===== Menu ======" << endl;
        cout << "1. Vytvor tabulku" << endl;
        cout << "2. vytvorene tabulky" << endl;
        cout << "3. pristupne tabulky" << endl;
        cout << "4. exit" << endl;
        cin >> vstup;

        switch(vstup) {
            case 1: {
                vytvorTab();
                vstup = 99;
                break;
            }
            case 2:{
                vypisVytvoreneTab();
                vstup = 99;
                break;
            }
            case 3:{
                vypisPristupneTab();
                vstup = 99;
                break;
            }
        }

    } while (vstup != 4);


}

bool Menu::jeCislo(string cislo) {
    if (cislo.find_first_not_of( "0123456789-+." ) == std::string::npos) {
        return true;
    }
    return false;
}













