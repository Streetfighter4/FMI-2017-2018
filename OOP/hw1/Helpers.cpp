//
// Created by yasen on 3/20/18.
//

#include "Helpers.h"
#include "Wallets.h"
#include "Transactions.h"
#include "Orders.h"
#include "Constants.h"
#include <fstream>
#include <string.h>

using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::atof;


void start() {

    Wallet* walArr = nullptr;
    size_t sizeWal = readWalletsFromFileDB(walArr);

    Transaction* trArr = nullptr;
    size_t sizeTr = readTransationsFromFileDB(trArr);

    Order* ordArr = nullptr;
    size_t sizeOrd = readOrderFromFileDB(ordArr);

    unsigned int curr_max_id = maxCurrId(walArr, sizeWal);
    while (true) {
        char request[256];
        cin.getline(request, 256);
        char *token;
        char *array[4];
        token = strtok(request, " ");
        int i = 0;
        array[i] = token;
        while (token != NULL) {
            array[i++] = token;
            token = strtok(NULL, " ");
        }

        if (!strcmp(array[0], "add-wallet")) {
            Wallet wallet = compactWallet(curr_max_id, atof(array[1]), array[2]);
            addWalletInDB(&wallet, sizeWal);
            Transaction tr = compactTransaction(wallet.id, systemWalletId, wallet.fiatMoney / FMICoinExchangeRates);
            makeTransaction(&tr, sizeTr);
        } else if (!strcmp(array[0], "make-order")) {
            Order order = compactOrder(array[1], atof(array[2]), atoi(array[3]));
            makeOrder(&order, sizeWal, sizeTr, sizeOrd, walArr, trArr, ordArr);
        } else if(!strcmp(array[0], "wallet-info")) {
            walletInfo(atoi(array[1]), walArr, trArr, sizeWal, sizeTr);
        } else if(!strcmp(array[0], "attract-investors")) {
            attractInvestors(walArr, sizeWal, trArr, sizeTr);
        } else if(!strcmp(array[0], "quit")) {
            writeWalletsInFileDB(walArr, sizeWal);
            writeTransactionsInFileDB(trArr, sizeTr);
            writeOrdersInFileDB(ordArr, sizeOrd);
            return;
        }
        else {
            break;
        }
    }
    delete[] walArr;
}

void walletInfo(unsigned walletId, Wallet*& wallets, Transaction*& transactions, size_t sizeWal, size_t sizeTr) {
    bool walletExist = false;
    for (int i = 0; i < sizeWal; ++i) {
        if(wallets[i].id == walletId) {
            walletExist = true;
            cout << "Owner: " << wallets[i].owner << endl
                 << "Fiat money: " << wallets[i].fiatMoney << endl
                 << "FMICoins: " << countFMICoinsInWallet(walletId, transactions, sizeTr) << endl;
        }
    }
    if(!walletExist) {
        cout << "Wallet dont exist in DB, please try with other wallet: " << endl;
    }
}

void swapInvestors(Wallet& a, Wallet& b) {
    Wallet buff = a;
    a = b;
    b = buff;
}

void sortInvestors(Wallet*& wallets, size_t sizeWal, Transaction*& transactions, size_t sizeTr) {
    for (int i = 0; i < sizeWal; ++i) {
        for (int j = i+1; j < sizeWal; ++j) {
            if(countFMICoinsInWallet(wallets[i].id, transactions, sizeTr) <
                    countFMICoinsInWallet(wallets[j].id, transactions, sizeTr)) {
                swapInvestors(wallets[i], wallets[j]);
            }
        }
    }
}


void attractInvestors(Wallet*& wallets, size_t sizeWal, Transaction*& transactions, size_t sizeTr) {
    sortInvestors(wallets, sizeWal, transactions, sizeTr);
    for (int i = 0; i < 10; ++i) {
        cout << i<< ": " << "FMI Coins: " << countFMICoinsInWallet(wallets[i].id, transactions, sizeTr) << ", "
                         << "Count orders: " << "Non, " //TODO
                         << "First order time: " << "Non, " //TODO
                         << "Last order time: " << "Non" << endl; //TODO

    }
}

double countFMICoinsInWallet(const unsigned walletId, Transaction*& transactions, const size_t size) {
    double startFMICoins = 0;

    for (int i = 0; i < size; ++i) {
        if(transactions[i].senderId == systemWalletId)
            startFMICoins = transactions[i].fmiCoins;
    }
    for (int i = 0; i < size; ++i) {
        if(transactions[i].senderId == walletId)
            startFMICoins -= transactions[i].fmiCoins;
        if(transactions[i].receiverId == walletId)
            startFMICoins += transactions[i].fmiCoins;
    }
    return startFMICoins;
}

double countFiatMoneyInWallet(const unsigned walletId, Wallet*& wallets, const size_t sizeWal) {
    for (int i = 0; i < sizeWal; ++i) {
        if(wallets[i].id == walletId)
            return wallets[i].fiatMoney;
    }
}

void exchangeMoney(Wallet*& wallets, size_t sizeWal, unsigned receiverId, unsigned senderId, double fmiCoins) {
    for (int i = 0; i < sizeWal; ++i) {
        if (wallets[i].id == receiverId)
            wallets[i].fiatMoney -= fmiCoins*FMICoinExchangeRates;
        if (wallets[i].id == senderId)
            wallets[i].fiatMoney += fmiCoins*FMICoinExchangeRates;
    }
}

void makeSellOrder(Order* newOrder, size_t sizeWal, size_t& sizeTr, size_t& sizeOrd,
                   Wallet*& wallets, Transaction*& transactions, Order*& orders) {
    if(!walletExistInDB(newOrder->walletId, wallets, sizeOrd)) {
        cout << "Wallet dont exist in DB, please try with other wallet: " << endl;
        return;
    }
    if(!(countFMICoinsInWallet(newOrder->walletId, transactions, sizeOrd) >= newOrder->fmiCoins)) {
        cout << "Wallet dont have enough FMICoins. Try later :)" << endl;
        return;

    }
    for (int i = 0; i < sizeOrd; ++i) {
        if(orders[i].type == Order::BUY && newOrder->fmiCoins != 0) {
            Transaction transaction;
            if(orders[i].fmiCoins <= newOrder->fmiCoins) {
                transaction = compactTransaction(newOrder->walletId, orders[i].walletId, orders[i].fmiCoins);
                makeTransaction(&transaction, sizeTr);
                exchangeMoney(wallets, sizeWal, newOrder->walletId, orders[i].walletId, orders[i].fmiCoins);
                newOrder->fmiCoins -= orders[i].fmiCoins;

                for (int j = i+1; j < sizeOrd; ++j) {
                    orders[j] = orders[j-1];
                }
                sizeOrd--;
            } else {
                transaction = compactTransaction(newOrder->walletId, orders[i].walletId, newOrder->fmiCoins);
                makeTransaction(&transaction, sizeTr);
                exchangeMoney(wallets, sizeWal, newOrder->walletId, orders[i].walletId, newOrder->fmiCoins);
                orders[i].fmiCoins -= newOrder->fmiCoins;
            }
        }
    }
    if(newOrder->fmiCoins > 0) {
        Order* newMem = new (std::nothrow) Order[sizeOrd + 1];

        if (newMem == nullptr) {
            cout << "Can't add : no memory !" << endl;
            return;
        }
        memcpy(newMem, orders, sizeof(Order)*sizeOrd);
        newMem[sizeOrd] = *newOrder;
        delete[] orders;
        orders = newMem;
        ++sizeOrd;
    }
}

void makeBuyOrder(Order* newOrder, size_t sizeWal, size_t& sizeTr, size_t& sizeOrd,
                  Wallet*& wallets, Transaction*& transactions, Order*& orders) {
    if(!walletExistInDB(newOrder->walletId, wallets, sizeOrd)) {
        cout << "Wallet dont exist in DB, please try with other wallet: " << endl;
        return;
    }
    if(!(countFiatMoneyInWallet(newOrder->walletId, wallets, sizeWal) >= newOrder->fmiCoins)) {
        cout << "Wallet dont have enough FMICoins. Try later :)" << endl;
        return;

    }
    for (int i = 0; i < sizeOrd; ++i) {
        if(orders[i].type == Order::SELL && newOrder->fmiCoins != 0) {
            Transaction transaction;
            if(orders[i].fmiCoins <= newOrder->fmiCoins) {
                transaction = compactTransaction(orders[i].walletId, newOrder->walletId, orders[i].fmiCoins);
                makeTransaction(&transaction, sizeTr);
                exchangeMoney(wallets, sizeWal, orders[i].walletId, newOrder->walletId, orders[i].fmiCoins);
                newOrder->fmiCoins -= orders[i].fmiCoins;

                for (int j = i+1; j < sizeOrd; ++j) {
                    orders[j] = orders[j-1];
                }
                sizeOrd--;
            } else {
                transaction = compactTransaction(orders[i].walletId, newOrder->walletId, newOrder->fmiCoins);
                makeTransaction(&transaction, sizeTr);
                exchangeMoney(wallets, sizeWal, orders[i].walletId, newOrder->walletId, newOrder->fmiCoins);
                orders[i].fmiCoins -= newOrder->fmiCoins;
            }
        }
    }
    if(newOrder->fmiCoins > 0) {
        Order* newMem = new (std::nothrow) Order[sizeOrd + 1];

        if (newMem == nullptr) {
            cout << "Can't add : no memory !" << endl;
            return;
        }
        memcpy(newMem, orders, sizeof(Order)*sizeOrd);
        newMem[sizeOrd] = *newOrder;
        delete[] orders;
        orders = newMem;
        ++sizeOrd;
    }
}

void makeOrder(Order* newOrder, size_t& sizeWal, size_t& sizeTr, size_t& sizeOrd,
               Wallet*& wallets, Transaction*& transactions, Order*& orders) {
    if (newOrder == nullptr) {
        cout << "Order is failed...\n";
        return;
    }
    if(newOrder->type == newOrder->SELL) {
        makeSellOrder(newOrder, sizeWal, sizeTr, sizeOrd, wallets, transactions, orders);
    }
    if(newOrder->type == newOrder->BUY) {
        makeBuyOrder(newOrder, sizeWal, sizeTr, sizeOrd, wallets, transactions, orders);
    }
    cout << newOrder->walletId << endl
         << newOrder->fmiCoins << endl
         << newOrder->type << endl;
    writeWalletsInFileDB(wallets, sizeWal);
    writeTransactionsInFileDB(transactions, sizeTr);
    writeOrdersInFileDB(orders, sizeOrd);
}

Transaction compactTransaction(unsigned senderId, unsigned receiverId, double fmiCoins) {
    Transaction tr;
    tr.time = time(0);
    tr.fmiCoins = fmiCoins;
    cout << "fmiCoins: " << tr.fmiCoins << endl;
    tr.senderId = senderId;
    tr.receiverId = receiverId;
    return tr;
}

