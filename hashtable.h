#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include "stock.h"

/**
 * Represents a HashTable for saving stock information
 */
class HashTable {
    const static int array_size = 1999;
    // Data format to store stocks in
    Stock* stocks[array_size];

public:
    const static int HASH_BY_NAME = 0;
    const static int HASH_BY_CODE = 1;
    /**
     * Creates a new HashTable
     */
    HashTable();
    /**
     * Removes a HashTable
     */
    ~HashTable();
    /**
     * Hash function, which creates an integer value from a string
     * @param str string to be hashed
     * @return an integer value representing a hashed value of the given string
     */
    int hash(std::string str);
    /**
     * Puts a stock into the HashTable
     * @param stock Stock to be inserted
     * @param hash_by HASH_BY_NAME or HASH_BY_CODE
     */
    void add(Stock* stock, int hash_by);
    /**
     * Removes a stock from the HashTable
     * @param name Name of stock to be removed
     * @param hash_by HASH_BY_NAME or HASH_BY_CODE
     */
    void remove(std::string name, int hash_by);
    /**
     * Searches a stock in the HashTable and returns it if found
     * @param name Name of wanted stock
     * @param hash_by HASH_BY_NAME or HASH_BY_CODE
     * @return Wanted stock, if found. Else it will return null
     */
    Stock* search(std::string name, int hash_by);
    /**
     * Saves the complete HashTable into a file
     * @param filepath the path (+filename) where it should be saved
     */
    void saveToFile(std::string filepath);
    /**
     * Reads a complete HashTable from a file
     * @param filepath the path (+filename) from where it should be read
     */
    void readFromFile(std::string filepath);

};

#endif //HASHTABLE_HASHTABLE_H
