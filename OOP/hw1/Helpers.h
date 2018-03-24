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
void walletInfo(unsigned walletId, Wallet*& wallets, Transaction*& transactions, size_t sizeWal, size_t sizeTr);

void attractInvestors(Wallet*& wallets, size_t sizeWal, Transaction*& transactions, size_t sizeTr);
double countFMICoinsInWallet(const unsigned, Transaction*&, const size_t);
double countFiatMoneyInWallet(const unsigned walletId, Wallet*& wallets, const size_t sizeWal);

void exchangeMoney(Wallet*& wallets, size_t sizeWal, unsigned receiverId, unsigned senderId, double fmiCoins);


void makeSellOrder(Order* newOrder, size_t sizeWal, size_t& sizeTr, size_t& sizeOrd,
                   Wallet*& wallets, Transaction*& transactions, Order*& orders);

void makeBuyOrder(Order* newOrder, size_t sizeWal, size_t& sizeTr, size_t& sizeOrd,
                  Wallet*& wallets, Transaction*& transactions, Order*& orders);

void makeOrder(Order*, size_t&, size_t&, size_t&, Wallet*&, Transaction*&, Order*&);

Transaction compactTransaction(unsigned , unsigned, double);

#endif //HW1_HELPERS_H
