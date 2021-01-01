//
// Created by Michal on 1. 1. 2021.
//

#include "Server.h"
#include <iostream>

int main(int argc, char *argv[]){
    if (argc < 2) {
        cout << "Neni zadana port" << endl;
        return 1;
    }

    Server* server_test = new Server(atoi(argv[1]));


    // TODO ako bude predavat spravy server dalej
    //
    server_test->posliSpravu( ,"Dostal som Halo!");

    delete server_test;
    return 0;
}