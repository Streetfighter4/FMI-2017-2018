//
// Created by yasen on 3/19/18.
//

#ifndef HW1_WALLETS_H
#define HW1_WALLETS_H

#include <iostream>
#include <fstream>
struct Wallet {
    char owner[256];
    unsigned id;
    double fiatMoney;
};
struct Transaction;
unsigned maxCurrId(Wallet*& arrWal, size_t size);
void addWalletInDB(Wallet*, size_t&);
void writeWalletsInFileDB(const Wallet*, size_t);
size_t readWalletsFromFileDB(Wallet*& );
bool walletExistInDB(const unsigned, Wallet*&, const size_t);
double countFMICoinsInWallet(const unsigned, Transaction*&, const size_t);
Wallet compactWallet(unsigned, double, char*);

#endif //HW1_WALLETS_H
