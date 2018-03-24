//
// Created by yasen on 3/24/18.
//

#ifndef HW1_TRANSACTIONS_H
#define HW1_TRANSACTIONS_H

#include <time.h>
#include <fstream>
#include <string.h>
#include <iostream>


struct Transaction {
    long long time;
    unsigned senderId;
    unsigned receiverId;
    double fmiCoins;
};

size_t readTransationsFromFileDB(Transaction*&);
void makeTransaction(Transaction*, size_t&);
struct Wallet;
Transaction compactTransaction(Wallet&, unsigned);
void writeTransactionsInFileDB(const Transaction*, size_t);

#endif //HW1_TRANSACTIONS_H
