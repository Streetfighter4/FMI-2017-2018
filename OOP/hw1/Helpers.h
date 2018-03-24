//
// Created by yasen on 3/20/18.
//

#ifndef HW1_HELPERS_H
#define HW1_HELPERS_H

#include <iostream>
void start();

struct Transaction;
struct Wallet;
struct Order;
double countFMICoinsInWallet(const unsigned, Transaction*&, const size_t);

void makeOrder(const Order*, size_t&, Wallet*&, Transaction*&);

Transaction compactTransaction(Wallet&, unsigned);

#endif //HW1_HELPERS_H
