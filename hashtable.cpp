#include <string.h>
#include <math.h>
#include "hashtable.h"

HashTable::HashTable() {
    for(int i = 0; i < array_size; i++){
        stocks[i] = nullptr;
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

    return(sum % array_size);
}

void HashTable::add(Stock* stock, int hash_by) {
    int hashed = 0;
    if(hash_by == HASH_BY_NAME) {
        hashed = hash(stock->getName());
    }else{
        hashed = hash(stock->getMemberCode());
    }
    if(stocks[hashed] == nullptr){
        stocks[hashed] = stock;
    }else{
        int plus = 1;
        int next_pos = 0;
        for(int i = 1; i <= array_size;){
            int x = (int)pow(i,2);
            if(!plus){
                x = (-1) * x;
                i++;
            }
            plus = (plus+1)%2;
            next_pos = hashed+x;
            if(next_pos<0){
                next_pos = array_size-next_pos;
            }
            if(stocks[next_pos%array_size] == nullptr){
                stocks[next_pos%array_size] = stock;
                break;
            }
        }
    }
}

void HashTable::remove(std::string name, int hash_by) {
    // TODO: delete allocated memory
    int hashed = hash(name);
    if((hash_by == HASH_BY_NAME && stocks[hashed]->getName() == name) ||
            (hash_by == HASH_BY_CODE && stocks[hashed]->getMemberCode() == name)){
        delete stocks[hashed];
        stocks[hashed] = nullptr;
    }else{
        int plus = 1;
        int next_pos = 0;
        for(int i = 1; i <= array_size;){
            int x = (int)pow(i,2);
            if(!plus){
                x = (-1) * x;
                i++;
            }
            plus = (plus+1)%2;
            next_pos = hashed+x;
            if(next_pos<0){
                next_pos = array_size-next_pos;
            }
            if((hash_by == HASH_BY_NAME && stocks[next_pos%array_size]->getName() == name) ||
                    (hash_by == HASH_BY_CODE && stocks[next_pos%array_size]->getMemberCode() == name)){
                delete stocks[next_pos%array_size];
                stocks[next_pos%array_size] = nullptr;
                break;
            }
        }
    }
}

Stock HashTable::search(std::string name, int hash_by) {
    // TODO: search stock in hashtable
}