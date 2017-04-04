#include <string.h>
#include <math.h>
#include <fstream>
#include <sstream>
#include "hashtable.h"

HashTable::HashTable() {
    for(int i = 0; i < array_size; i++){
        stocks[i] = nullptr;
    }
}

HashTable::~HashTable(){
    for(int i = 0; i < array_size; i++){
        if(stocks[i] != nullptr){
            delete stocks[i];
        }
    }
    delete[] &stocks;
}

int HashTable::hash(std::string str) {
    int intLength = str.length() / 4;
    long sum = 0;
    for (int j = 0; j < intLength; j++) {
        char c[4];
        std::string tmp = str.substr(j * 4, (j * 4) + 4);
        strcpy(c, tmp.c_str());
        long mult = 1;
        for (int k = 0; k < 4; k++) {
            sum += c[k] * mult;
            mult *= 256;
        }
    }

    int lengthMax = str.length() % 4;
    char c[lengthMax];
    std::string tmp = str.substr(intLength * 4);
    strcpy(c, tmp.c_str());
    long mult = 1;
    for (int k = 0; k < lengthMax; k++) {
        sum += c[k] * mult;
        mult *= 256;
    }

    sum = (sum % array_size + array_size) % array_size;

    return(sum);
}

void HashTable::add(Stock* stock, int hash_by) {
    int hashed = 0;
    if(hash_by == HASH_BY_NAME) {
        hashed = hash(stock->getName());
    }else{
        hashed = hash(stock->getMemberCode());
    }
    //look in the list if the hashed position for stock is empty
    if(stocks[hashed] == nullptr){
        stocks[hashed] = stock;
    }else{
        //if not empty start the search algorithm for empty position
        int plus = 1;
        int next_pos = 0;
        for(int i = 1; i <= array_size;){
            int x = (int)pow(i,2);
            //function to take the numbers of square always negative and positive
            if(!plus){
                x = (-1) * x;
                i++;
            }
            plus = (plus+1)%2;
            //calculation to get the correct value always as a positive integer
            next_pos = ((hashed+x)% array_size + array_size) % array_size ;
            if(stocks[next_pos] == nullptr){
                stocks[next_pos] = stock;
                break;
            }
        }
    }
}

void HashTable::remove(std::string name, int hash_by) {
    int hashed = hash(name);
    //look in the list if correct stock from the input is on the hashed position
    if((hash_by == HASH_BY_NAME && stocks[hashed] != nullptr && stocks[hashed]->getName() == name) ||
            (hash_by == HASH_BY_CODE && stocks[hashed] != nullptr && stocks[hashed]->getMemberCode() == name)){
        delete stocks[hashed];
        stocks[hashed] = nullptr;
    }else{
        int plus = 1;
        int next_pos = 0;
        for(int i = 1; i <= array_size;){
            int x = (int)pow(i,2);
            //function to take the numbers of square always negative and positive
            if(!plus){
                x = (-1) * x;
                i++;
            }
            plus = (plus+1)%2;
            //calculation to get the correct value always as a positive integer
            next_pos = ((hashed+x) % array_size + array_size) % array_size ;
            if((hash_by == HASH_BY_NAME && stocks[next_pos] != nullptr && stocks[next_pos]->getName() == name) ||
                    (hash_by == HASH_BY_CODE && stocks[next_pos] != nullptr && stocks[next_pos]->getMemberCode() == name)){
                delete stocks[next_pos];
                stocks[next_pos] = nullptr;
                break;
            }
        }
    }
}

Stock* HashTable::search(std::string name, int hash_by) {
    int hashed = hash(name);
    //look in the list if correct stock from the input is on the hashed position
    if((hash_by == HASH_BY_NAME && stocks[hashed] != nullptr && stocks[hashed]->getName() == name) ||
       (hash_by == HASH_BY_CODE && stocks[hashed] != nullptr && stocks[hashed]->getMemberCode() == name)){
        return stocks[hashed];
    }else{
        //if not on the hashed position start with the search algorithm
        int plus = 1;
        int next_pos = 0;
        for(int i = 1; i <= array_size;){
            int x = (int)pow(i,2);
            //function to take the numbers of square always negative and positive
            if(!plus){
                x = (-1) * x;
                i++;
            }
            plus = (plus+1)%2;
            //calculation to get the correct value always as a positive integer
            next_pos = ((hashed+x) % array_size + array_size) % array_size ;
            if(hash_by == HASH_BY_NAME && stocks[next_pos] != nullptr && stocks[next_pos]->getName() == name ||
               hash_by == HASH_BY_CODE && stocks[next_pos] != nullptr && stocks[next_pos]->getMemberCode() == name){
                return stocks[next_pos];
            }
        }
    }
    return nullptr;
}

void HashTable::saveToFile(std::string filepath) {
    int count_pricedata;
    std::ofstream file;
    file.open(filepath, std::ios::out);

    for(int i = 0; i < array_size; i++){
        if(stocks[i] != nullptr){
            // Write stock information
            file << i << " " << stocks[i]->getName() << " " << stocks[i]->getMemberCode() << " " << stocks[i]->getSIN();
            count_pricedata = 0;
            for(int j = 0; j < 30; j++){
                if(stocks[i]->getPriceData()[j] != nullptr){
                    count_pricedata++;
                }
            }
            file << " " << count_pricedata << "\n";
            // Write price data
            for(int j = 0; j < 30; j++){
                if(stocks[i]->getPriceData()[j] != nullptr){
                    file << j << " " << stocks[i]->getPriceData()[j]->getDate();
                    file << " " << stocks[i]->getPriceData()[j]->getOpen();
                    file << " " << stocks[i]->getPriceData()[j]->getHigh();
                    file << " " << stocks[i]->getPriceData()[j]->getLow();
                    file << " " << stocks[i]->getPriceData()[j]->getClose();
                    file << " " << stocks[i]->getPriceData()[j]->getVolume();
                    file << " " << stocks[i]->getPriceData()[j]->getAdjClose() << "\n";
                }
            }
        }
    }

    // End of File
    file << "eof" << " \n";

    file.close();
}

void HashTable::readFromFile(std::string filepath) {
    std::string in, name, membercode, sin_s, date;
    int count_pricedata, sin, index, volume, pdindex;
    double open, high, low, close, adjclose;
    std::ifstream file;
    file.open(filepath, std::ios::in);

    for(int i = 0; i < array_size; i++){
        getline(file, in, ' ');
        // If not end of file
        if(in != "eof"){
            // Read stock information
            getline(file, name, ' ');
            getline(file, membercode, ' ');
            getline(file, sin_s, ' ');
            std::stringstream sin_stream(sin_s);
            sin_stream >> sin;
            std::stringstream index_stream(in);
            index_stream >> index;
            // Insert stock into hashtable
            Stock* stock = new Stock(name, membercode, sin);
            stocks[index] = stock;

            // Read price data
            getline(file, in, '\n');
            std::stringstream pricedata_stream(in);
            pricedata_stream >> count_pricedata;

            PriceData* data[30];
            for(int j = 0; j < 30; j++){
                data[j] = nullptr;
            }
            for(int j = 0; j < count_pricedata; j++){
                getline(file, in, ' ');
                {
                    std::stringstream in_stream(in);
                    in_stream >> pdindex;
                    getline(file, date, ' ');
                }
                getline(file, in, ' ');
                {
                    std::stringstream in_stream(in);
                    in_stream >> open;
                }
                getline(file, in, ' ');
                {
                    std::stringstream in_stream(in);
                    in_stream >> high;
                }
                getline(file, in, ' ');
                {
                    std::stringstream in_stream(in);
                    in_stream >> low;
                }
                getline(file, in, ' ');
                {
                    std::stringstream in_stream(in);
                    in_stream >> close;
                }
                getline(file, in, ' ');
                {
                    std::stringstream in_stream(in);
                    in_stream >> volume;
                }
                getline(file, in, '\n');
                {
                    std::stringstream in_stream(in);
                    in_stream >> adjclose;
                }

                PriceData* priceData = new PriceData(date, open, high, low, close, volume, adjclose);
                data[pdindex] = priceData;
            }
            stocks[index]->setPriceData(data);
        }else{
            break;
        }
    }

    file.close();
}