//
// Created by Michal on 30. 12. 2020.
//

#ifndef UNTITLED6_TABULKA_H
#define UNTITLED6_TABULKA_H

#include <string>
#include <vector>
using namespace std;

class Tabulka {
public:
    Tabulka();
    ~Tabulka();

    bool pridajZaznam(string zaznam); // prida zaznam do csv suboru, database musi pripravit vhodny zaznam
    int hladatUIDZaznam(int cisloStlpca, string hladanaHodnota); // vrati cislo zaznamu/UID na ktorom je zaznam, cisloStlpca je atribut podla ktoreho hladame
    bool vymazZaznam(int cisloZaznamu); // vymaze riadok
    bool aktualizujZaznam(int UIDZaznamu, string zaznam); // TODO substringy co dostaneme hodnotu kt chceme menit alebo zmeneny zanam?
    string dajZaznam(int UIDZaznamu);

    void nastavPristup(string zaznamPristupu);
    int getUIDPouzivatela(int ID);
    string getPistup(int UIDzaznamu);

    vector<string> vypisUtriedenuTabulku(int stlpecNaUtriedenie);
    vector<string> vypisTabulka();

private:
    vector<string> data;
    vector<string> tabPristupy;
    string nazvyStlpcov;
};


#endif //UNTITLED6_TABULKA_H
