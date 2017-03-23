#include "stock.h"

PriceData::PriceData(std::string date, double open, double high, double low, double close, int volume, double adj_close)
        : date(date), open(open), high(high), low(low), close(close), volume(volume), adj_close(adj_close) {
}

Stock::Stock(std::string name, std::string member_code, int sin) : name(name), member_code(member_code), sin(sin) {
    for(int i = 0; i < 30 ; i++){
        price_data[i] = nullptr;
    }
}

Stock::Stock() {
    name = nullptr;
    member_code = nullptr;
    sin = -1;
}

void Stock::import_price_data(std::string filepath) {
    // TODO: import price data for 30 days from given csv file and save into vector price_data


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