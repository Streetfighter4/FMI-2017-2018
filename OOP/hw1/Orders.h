//
// Created by yasen on 3/24/18.
//

#ifndef HW1_ORDERS_H
#define HW1_ORDERS_H

#include <iostream>
#include <fstream>
#include <string.h>
struct Order {
    enum Type { SELL, BUY } type;
    unsigned walletId;
    double fmiCoins;
};


size_t readOrderFromFileDB(Order*&);
struct Wallet;
struct Transaction;
void makeOrder(const Order*, size_t&, Wallet*&, Transaction*&);

Order compactOrder(char*, double, unsigned);

void writeOrdersInFileDB(const Order*, size_t);

#endif //HW1_ORDERS_H
