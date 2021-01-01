//
// Created by Michal on 1. 1. 2021.
//

#include "klient.h"
#include <iostream>

int main(int argc, char *argv[]){
    if (argc < 3) {
        cout << "Neni zadana ip alebo port" << endl;
        return 1;
    }

    Klient* klient_test = new Klient(argv[1], atoi(argv[2]));

    klient_test->posliSpravu("Halo!");
    klient_test->precitaj("Halo!");




    delete klient_test;
    return 0;
}