#include <iostream>

#include "hashtable.h"

int main() {

    std::string in = "";
    HashTable *table = new HashTable();

    while(in.compare("QUIT") != 0){
        std::cin >> in;
        if(in.compare("ADD") == 0){

        }else if(in.compare("DEL") == 0){

        }else if(in.compare("IMPORT") == 0){

        }else if(in.compare("SEARCH") == 0){

        }else if(in.compare("PLOT") == 0){

        }else if(in.compare("SAVE") == 0){

        }else if(in.compare("LOAD") == 0){

        }
    }

    std::cout << "Exiting program..." << std::endl;
    std::cout << "Good Bye!" << std::endl;

    return 0;
}