#include "stock.h"
#include <fstream>
#include <sstream>
#include <cstring>

PriceData::PriceData(std::string date, double open, double high, double low, double close, int volume, double adj_close)
        : date(date), open(open), high(high), low(low), close(close), volume(volume), adj_close(adj_close) {
}

std::string PriceData::getDate() {
    return date;
}

double PriceData::getOpen() {
    return open;
}

double PriceData::getHigh() {
    return high;
}

double PriceData::getLow() {
    return low;
}

double PriceData::getClose() {
    return close;
}

int PriceData::getVolume() {
    return volume;
}

double PriceData::getAdjClose() {
    return adj_close;
}


Stock::Stock(std::string name, std::string member_code, int sin) : name(name), member_code(member_code), sin(sin) {
    for (int i = 0; i < 30; i++) {
        price_data[i] = nullptr;
    }
}

Stock::Stock() {
    name = nullptr;
    member_code = nullptr;
    sin = -1;
}

void Stock::import_price_data(std::string filepath) {
    std::ifstream file(filepath, std::ios::in);
    std::string line;
    int line_numbers = 0;
    for (; std::getline(file, line); line_numbers++);

    std::string date, open, high, low, close, volume, adj_close;
    double open_d, high_d, low_d, close_d, adj_close_d;
    int volume_d;
    std::ifstream datei;
    //open file with correct Filepath of Input
    datei.open(filepath, std::ios::in);
    //read first line without values to get to second line
    getline(datei, date, '\n');
    for (int i = 0; i < 30 && i < line_numbers-1; ++i) {
        //read the line of the file and get the values into the correct variables
        getline(datei, date, ',');
        getline(datei, open, ',');
        getline(datei, high, ',');
        getline(datei, low, ',');
        getline(datei, close, ',');
        getline(datei, volume, ',');
        getline(datei, adj_close, '\n');
        //prepare stringstreams to get the values from string into double
        std::stringstream open_s(open);
        std::stringstream high_s(high);
        std::stringstream low_s(low);
        std::stringstream close_s(close);
        std::stringstream volume_s(volume);
        std::stringstream adj_close_s(adj_close);
        //convert stringstreams in doubles
        open_s >> open_d;
        high_s >> high_d;
        low_s >> low_d;
        close_s >> close_d;
        adj_close_s >> adj_close_d;
        volume_s >> volume_d;
        //create new object and write correct values into it
        if(!open_s.fail() && !high_s.fail() && !low_s.fail() && !close_s.fail() && !adj_close_s.fail() && !volume_s.fail()) {
            if(price_data[i] != nullptr) {
                delete price_data[i];
            }
            price_data[i] = new PriceData(date, open_d, high_d, low_d, close_d, volume_d, adj_close_d);
        }
    }
}

std::string Stock::getName() {
    return name;
}

std::string Stock::getMemberCode() {
    return member_code;
}

int Stock::getSIN() {
    return sin;
}

PriceData** Stock::getPriceData() {
    return price_data;
}

void Stock::setPriceData(PriceData **data) {
    for(int i = 0; i < 30; i++){
        price_data[i] = data[i];
    }
}