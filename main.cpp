#include <iostream>
#include <sstream>
#include <array>
#include <iomanip>
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
                table_names->remove(s->getName(), HashTable::HASH_BY_NAME);
                table_codes->remove(s->getMemberCode(), HashTable::HASH_BY_CODE);
                std::cout << name << " successfully removed!" << std::endl;
            }else{
                std::cout << "Could not delete stock! (Not found)";
            }
        }else if(in.compare("IMPORT") == 0){
            std::string name;
            std::cout << "Name/Member Code: ";
            std::cin >> name;
            Stock* s = searchStock(name, table_names, table_codes);
            if(s != nullptr) {
                std::string filepath;
                std::cout << "Filepath: ";
                std::cin >> filepath;
                s->import_price_data(filepath);
                std::cout << "Import successful!" << std::endl;
            }else{
                std::cout << "Could not find stock!"  << std::endl;
            }

        }else if(in.compare("SEARCH") == 0){
            std::string name;
            std::cout << "Name/Member Code: ";
            std::cin >> name;
            Stock* s = searchStock(name, table_names, table_codes);
            if(s != nullptr) {
                std::cout << "NAME: " << s->getName() << std::endl;
                std::cout << "MEMBER CODE: " << s->getMemberCode() << std::endl;
                std::cout << "SIN: " << s->getSIN() << std::endl;
                PriceData* data = s->getPriceData()[0];
                if(data != nullptr) {
                    std::cout << "High: " << data->getHigh() << std::endl;
                }
            }else{
                std::cout << "Could not find stock!";
            }
        }else if(in.compare("PLOT") == 0){
            std::string name;
            std::cout << "Name/Member Code: ";
            std::cin >> name;
            Stock* s = searchStock(name, table_names, table_codes);
            if(s != nullptr) {
                constexpr size_t entries = 30;
                constexpr size_t steps   = 25;
                std::array<int, entries> arr;
                double max = 0;
                PriceData* data = nullptr;
                for (int i = 0; i < entries; ++i) {
                    data = s->getPriceData()[i];
                    if (data != nullptr)
                        max = std::max(max, data->getHigh());
                }
                //
                auto adjust = max / steps;
                for (int i = 0; i < entries; ++i) {
                    data = s->getPriceData()[i];
                    arr[i] = (data != nullptr) ? data->getHigh() / adjust : 0;
                }
                // plot
                std::cout << "\n" << std::endl; // clear new line...
                for (int j = steps; j > 0; j--) {
                    for (int i = 0; i < entries; ++i)
                        if (arr[i] >= j)
                            std::cout << " # ";
                        else
                            std::cout << "   ";
                    std::cout << " " << j*adjust << std::endl;
                }
                int count = 30;
                for (int j = entries; j > 0; j--) {
                    if(count < 10) {
                        std::cout << " " << std::setw(2) << std::left  << count;
                    }else{
                        std::cout << " " << count;
                    }
                    count --;
                }



            }else{
                std::cout << "Could not find stock!";
            }
        }else if(in.compare("SAVE") == 0){
            std::cout << "Saving to file..." << std::endl;
            table_names->saveToFile("hashtable_names.txt");
            table_codes->saveToFile("hashtable_codes.txt");
            std::cout << "Saved!" << std::endl;
        }else if(in.compare("LOAD") == 0){
            std::cout << "Reading from file..." << std::endl;
            table_names->readFromFile("hashtable_names.txt");
            table_codes->readFromFile("hashtable_codes.txt");
            std::cout << "Finished!" << std::endl;
        }
    }

    std::cout << "Exiting program..." << std::endl;
    std::cout << "Good Bye!" << std::endl;

    return 0;
}