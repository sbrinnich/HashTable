#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include "stock.h"

/**
 * Represents a HashTable for saving stock information
 */
class HashTable {
    // TODO: find data format to store stocks in
public:
    /**
     * Creates a new HashTable
     */
    HashTable();
    /**
     * Puts a stock into the HashTable
     * @param stock Stock to be inserted
     */
    void add(Stock stock);
    /**
     * Removes a stock from the HashTable
     * @param name Name of stock to be removed
     */
    void remove(std::string name);
    /**
     * Searches a stock in the HashTable and returns it if found
     * @param name Name of wanted stock
     * @return Wanted stock, if found. Else it will return null
     */
    Stock search(std::string name);
};

#endif //HASHTABLE_HASHTABLE_H
