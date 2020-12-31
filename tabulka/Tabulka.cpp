//
// Created by Michal on 30. 12. 2020.
//

#include "Tabulka.h"

Tabulka::Tabulka() {

}

Tabulka::~Tabulka() {

}

bool Tabulka::pridajZaznam(string zaznam) {
    return false;
}

int Tabulka::hladatUIDZaznam(int cisloStlpca, string hladanaHodnota) {
    return 0;
}

bool Tabulka::vymazZaznam(int cisloZaznamu) {
    return false;
}

bool Tabulka::aktualizujZaznam(int UIDZaznamu, string zaznam) {
    return false;
}

string Tabulka::dajZaznam(int UIDZaznamu) {
    return std::__cxx11::string();
}

void Tabulka::nastavPristup(string zaznamPristupu) {

}

int Tabulka::getUIDPouzivatela(int ID) {
    return 0;
}

string Tabulka::getPistup(int UIDzaznamu) {
    return std::__cxx11::string();
}

vector<string> Tabulka::vypisUtriedenuTabulku(int stlpecNaUtriedenie) {
    return vector<string>();
}

vector<string> Tabulka::vypisTabulka() {
    return vector<string>();
}
