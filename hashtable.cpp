#include "hashtable.h"
#include <string.h>
#include <math.h>

using namespace std;

HashTable::HashTable() {
    long sfold(string s, int M) {
        int intLength = s.length() / 4;
        long sum = 0;
        for (int j = 0; j < intLength; j++) {
            char c[5];
            string tmp = s.substr(j * 4, (j * 4) + 4);
            strcpy(c, tmp.c_str());
            long mult = 1;
            for (int k = 0; k < 5; k++) {
                sum += c[k] * mult;
                mult *= 256;
            }
        }

        int lengthMax = s.length() % 4;
        char c[lengthMax];
        string tmp = s.substr(intLength * 4);
        strcpy(c, tmp.c_str());
        long mult = 1;
        for (int k = 0; k < lengthMax; k++) {
            sum += c[k] * mult;
            mult *= 256;
        }

        cout << sum % 4 ;

        return(sum % M);
    }
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