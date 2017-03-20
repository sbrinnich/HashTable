#include <string.h>
#include "hashtable.h"

HashTable::HashTable() {
    stocks.reserve(array_size);
    for(int i = 0; i < array_size; i++){
        Stock *s = new Stock();
        stocks.push_back(s);
    }
}

int HashTable::hash(std::string str) {
    int intLength = str.length() / 4;
    long sum = 0;
    for (int j = 0; j < intLength; j++) {
        char c[5];
        std::string tmp = str.substr(j * 4, (j * 4) + 4);
        strcpy(c, tmp.c_str());
        long mult = 1;
        for (int k = 0; k < 5; k++) {
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

    //std::cout << sum % 4 ;

    return(sum % array_size);
}

void HashTable::add(Stock stock) {
    // TODO: add stock to hashtable
}

void HashTable::remove(std::string name) {
    // TODO: remove stock from hashtable
}

Stock HashTable::search(std::string name) {
    // TODO: search stock in hashtable
}