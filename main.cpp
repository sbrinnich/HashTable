#include <iostream>
#include <sstream>

#include "hashtable.h"

Stock* searchStock(std::string name, HashTable* table_names, HashTable* table_codes){
    Stock *s = nullptr;
    if(name.length() > 4) {
        s = table_names->search(name, HashTable::HASH_BY_NAME);
    }else{
        s = table_codes->search(name, HashTable::HASH_BY_CODE);
    }
    if(s == nullptr){
        if(name.length() > 4) {
            s = table_codes->search(name, HashTable::HASH_BY_CODE);
        }else{
            s = table_names->search(name, HashTable::HASH_BY_NAME);
        }
    }
    return s;
}

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
            Stock *s = searchStock(name, table_names, table_codes);
            if(s != nullptr) {
                if(name.length() > 4){
                    table_names->remove(s->getName(), HashTable::HASH_BY_NAME);
                    table_codes->remove(s->getMemberCode(), HashTable::HASH_BY_CODE);
                    std::cout << s->getName() << " removed!" << std::endl;
                }else{
                    table_names->remove(s->getName(), HashTable::HASH_BY_NAME);
                    table_codes->remove(s->getMemberCode(), HashTable::HASH_BY_CODE);
                    std::cout << s->getMemberCode() << " removed!" << std::endl;
                }


                table_names->remove(s->getName(), HashTable::HASH_BY_NAME);
                table_codes->remove(s->getMemberCode(), HashTable::HASH_BY_CODE);
                std::cout << name << " successfully removed!" << std::endl;
            }else{
                std::cout << "Could not delete stock! (Not found)";
            }
        }else if(in.compare("IMPORT") == 0){

        }else if(in.compare("SEARCH") == 0){
            std::string name;
            std::cout << "Name/Member Code: ";
            std::cin >> name;
            Stock* s = searchStock(name, table_names, table_codes);
            if(s != nullptr) {
                std::cout << "NAME: " << s->getName() << std::endl;
                std::cout << "MEMBER CODE: " << s->getMemberCode() << std::endl;
                std::cout << "SIN: " << s->getSIN() << std::endl;
                //TODO: plot latest price data
            }else{
                std::cout << "Could not find stock!";
            }
        }else if(in.compare("PLOT") == 0){
            std::string name;
            std::cout << "Name/Member Code: ";
            std::cin >> name;
            Stock* s = searchStock(name, table_names, table_codes);
            if(s != nullptr) {
                //TODO: plot
            }else{
                std::cout << "Could not find stock!";
            }
        }else if(in.compare("SAVE") == 0){

        }else if(in.compare("LOAD") == 0){

        }
    }

    std::cout << "Exiting program..." << std::endl;
    std::cout << "Good Bye!" << std::endl;

    return 0;
}