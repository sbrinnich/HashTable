#ifndef HASHTABLE_STOCK_H
#define HASHTABLE_STOCK_H

#include <iostream>
#include <vector>

/**
 * Represents price data of a stock for a single day
 */
class PriceData {
    std::string date;
    double open, high, low, close, adj_close;
    int volume;
public:
    /**
     * Creates price data for a single day
     * @param date Date of given price data
     * @param open Open value of given day
     * @param high High value of given day
     * @param low Low value of given day
     * @param close Close value of given day
     * @param volume Volume of given day
     * @param adj_close Adjusted close value of given day
     */
    PriceData(std::string date, double open, double high, double low, double close, int volume, double adj_close);

    double getHigh();
};

/**
 * Represents a stock with a name, member code, security identification number and price data of last 30 days
 */
class Stock {
    std::string name;
    std::string member_code;
    // Security Identification Number
    int sin;
    PriceData* price_data[30];
public:
    /**
     * Creates an empty stock
     */
     Stock();
    /**
     * Creates a new stock
     * @param name Stock name
     * @param member_code Short name of stock
     * @param sin Security Identification Number
     */
    Stock(std::string name, std::string member_code, int sin);
    /**
     * Import price data of last 30 days from a csv file
     * @param filepath path to csv file (including filename + ending)
     */
    void import_price_data(std::string filepath);
    /**
     * Returns the name of the stock
     * @return a string containing the name
     */
    std::string getName();
    /**
     * Returns the member code of the stock
     * @return a string containing the member code
     */
    std::string getMemberCode();
    /**
     * Returns the security identification number of the stock
     * @return an int containing the sin
     */
    int getSIN();

    double getPriceData();
};

#endif //HASHTABLE_STOCK_H
