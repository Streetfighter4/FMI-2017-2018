//
// Created by yasen on 3/24/18.
//

#ifndef HW1_ORDERS_H
#define HW1_ORDERS_H

#include <iostream>
struct Order {
    enum Type { SELL, BUY } type;
    unsigned walletId;
    double fmiCoins;


};


Order compactOrder(char*, double, unsigned);
size_t readOrderFromFileDB(Order*&);


void writeOrdersInFileDB(const Order*, size_t);

#endif //HW1_ORDERS_H
