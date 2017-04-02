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
    std::ifstream datei;                                    //erzeuge ifstream
    datei.open(filepath, std::ios::in);                     //öffne date mit übergebenen dateipfad
    getline(datei, date, '\n');                             //Lese erste Zeile aus
    for (int i = 0; i < 30 && i < line_numbers-1; ++i) {
        getline(datei, date, ',');                          // übertrage die Daten in der richtigen Reihenfolge auf die erzeugten strings
        getline(datei, open, ',');
        getline(datei, high, ',');
        getline(datei, low, ',');
        getline(datei, close, ',');
        getline(datei, volume, ',');
        getline(datei, adj_close, '\n');
        std::stringstream open_s(open);                      //erzeuge stringstreams aus allen eingelesenen Daten um sie in doubles/ints konvertieren zu können.
        std::stringstream high_s(high);
        std::stringstream low_s(low);
        std::stringstream close_s(close);
        std::stringstream volume_s(volume);
        std::stringstream adj_close_s(adj_close);
        open_s >> open_d;                                    //konvertiere stringstreams in korrektes dateiformat
        high_s >> high_d;
        low_s >> low_d;
        close_s >> close_d;
        adj_close_s >> adj_close_d;
        volume_s >> volume_d;
        if(!open_s.fail() && !high_s.fail() && !low_s.fail() && !close_s.fail() && !adj_close_s.fail() && !volume_s.fail()) { //erstelle neues Objekt und übergebe die daten
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