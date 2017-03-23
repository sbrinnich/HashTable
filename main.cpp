#include <iostream>
#include <sstream>

#include "hashtable.h"

int main() {

    std::string in = "";
    HashTable *table_names = new HashTable();
    HashTable *table_codes = new HashTable();

    while(in.compare("QUIT") != 0){
        std::cin >> in;
        if(in.compare("ADD") == 0){
            std::string name, member_code, sin_s;
            int sin;
            std::cout << "Name: ";
            std::cin >> name;
            std::cout << "Member Code: ";
            std::cin >> member_code;
            int fail = 0;
            do {
                std::cout << "Security Identification Number: ";
                std::cin >> sin_s;
                std::stringstream s(sin_s);
                s >> sin;
                if(s.fail()){
                    fail = 1;
                }else{
                    fail = 0;
                }
            }while(fail);
            Stock *stock = new Stock(name, member_code, sin);
            table_names->add(stock, HashTable::HASH_BY_NAME);
            table_codes->add(stock, HashTable::HASH_BY_CODE);
        }else if(in.compare("DEL") == 0){
            std::string name;
            std::cout << "Name/Member Code: ";
            std::cin >> name;
            Stock *s;
            if(name.length() > 4) {
                s = table_names->search(name, HashTable::HASH_BY_NAME);
            }else{
                s = table_names->search(name, HashTable::HASH_BY_CODE);
            }
            if(s == nullptr){
                if(name.length() > 4) {
                    s = table_names->search(name, HashTable::HASH_BY_CODE);
                }else{
                    s = table_names->search(name, HashTable::HASH_BY_NAME);
                }
            }
            if(s != nullptr) {
                table_names->remove(s->getName(), HashTable::HASH_BY_NAME);
                table_codes->remove(s->getMemberCode(), HashTable::HASH_BY_CODE);
            }else{
                std::cout << "Could not delete stock! (Not found)";
            }
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