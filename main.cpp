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

void printMenuInfo(){
    std::cout << "\n\n";
    std::cout << "==============================" << std::endl;
    std::cout << "1 ... Add stock" << std::endl;
    std::cout << "2 ... Search stock" << std::endl;
    std::cout << "3 ... Delete stock" << std::endl;
    std::cout << "4 ... Import price data from file" << std::endl;
    std::cout << "5 ... Plot price data of a stock" << std::endl;
    std::cout << "6 ... Save hashtable to file" << std::endl;
    std::cout << "7 ... Load hashtable from file" << std::endl;
    std::cout << "8 ... Quit program" << std::endl;
    std::cout << "------------------------------" << std::endl;
}

int main() {

    std::string in = "";
    HashTable *table_names = new HashTable();
    HashTable *table_codes = new HashTable();

    // QUIT if input is 8
    while(in.compare("8") != 0){
        printMenuInfo();
        std::cin >> in;
        if(in.compare("1") == 0){
            // ADD
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
        }else if(in.compare("3") == 0){
            // DELETE
            std::string name;
            std::cout << "Name/Member Code: ";
            std::cin >> name;
            Stock *s = searchStock(name, table_names, table_codes);
            if(s != nullptr) {
                table_names->remove(s->getName(), HashTable::HASH_BY_NAME);
                table_codes->remove(s->getMemberCode(), HashTable::HASH_BY_CODE);
                std::cout << name << " successfully removed!" << std::endl;
            }else{
                std::cout << "Could not delete stock! (Not found)" << std::endl;
            }
        }else if(in.compare("4") == 0){
            // IMPORT
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

        }else if(in.compare("2") == 0){
            // SEARCH
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
                }else{
                    std::cout << "No price data found" << std::endl;
                }
            }else{
                std::cout << "Could not find stock!" << std::endl;
            }
        }else if(in.compare("5") == 0){
            // PLOT
            std::string name;
            std::cout << "Name/Member Code: ";
            std::cin >> name;
            Stock* s = searchStock(name, table_names, table_codes);
            //check if the stock from input is available
            if(s != nullptr) {
                //define the size of the Plotting window
                constexpr size_t entries = 30;
                constexpr size_t steps   = 25;
                //the array/vector to put the values of the stock in it
                std::array<int, entries> arr;
                double max = 0;
                PriceData* data = nullptr;
                //get the max value of the chosen stock
                for (int i = 0; i < entries; ++i) {
                    data = s->getPriceData()[i];
                    if (data != nullptr)
                        max = std::max(max, data->getHigh());
                }
                //write every value of the last 30 days in the correct position of the array/vector
                auto adjust = max / steps;
                for (int i = 0; i < entries; ++i) {
                    data = s->getPriceData()[i];
                    arr[i] = (data != nullptr) ? data->getHigh() / adjust : 0;
                }
                // plot the graph of the stock
                std::cout << "\n" << std::endl; // clear new line...
                for (int j = steps; j > 0; j--) {
                    for (int i = 0; i < entries; ++i)
                        if (arr[i] >= j)
                            std::cout << "#";
                        else
                            std::cout << " ";
                    std::cout << " " << j*adjust << std::endl;
                }

                //function to add the correct numbers of day in under my plotted graph
                auto plot_numbers = [&](const std::vector<int>& in) {
                    for (auto& i : in) std::cout << i;
                    std::cout << std::endl;
                };
                plot_numbers(std::vector <int>{0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,3});
                plot_numbers(std::vector <int>{1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0});
            }else{
                std::cout << "Could not find stock!" << std::endl;
            }
        }else if(in.compare("6") == 0){
            // SAVE
            std::cout << "Saving to file..." << std::endl;
            table_names->saveToFile("hashtable_names.txt");
            table_codes->saveToFile("hashtable_codes.txt");
            std::cout << "Saved!" << std::endl;
        }else if(in.compare("7") == 0){
            // LOAD
            std::cout << "Reading from file..." << std::endl;
            table_names->readFromFile("hashtable_names.txt");
            table_codes->readFromFile("hashtable_codes.txt");
            std::cout << "Finished!" << std::endl;
        }
    }

    std::cout << "Exiting program..." << std::endl;
    delete table_names;
    delete table_codes;
    std::cout << "Good Bye!" << std::endl;

    return 0;
}