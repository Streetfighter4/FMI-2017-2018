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
    cout << "curr_max_id: " << curr_max_id << endl;
    cout << "SizeWal: " << sizeWal << endl;
    while (true) {
        char request[256];
        cin.getline(request, 256);
        char* token;
        char* array[4];
        token = strtok(request, " ");
        int i = 0;
        array[i] = token;
        while (token != NULL) {
            array[i++] = token;
            token = strtok(NULL, " ");
        }
        for(int i = 0; i < 4; ++i)
            cout << array[i] << endl;

        if(!strcmp(array[0], "add-wallet")){
            Wallet wallet = compactWallet(curr_max_id, atof(array[1]), array[2]);
            addWalletInDB(&wallet, sizeWal);
            Transaction tr = compactTransaction(wallet, systemWalletId);
            makeTransaction(&tr, sizeTr);
        } else if(!strcmp(array[0], "make-order")) {
            Order order = compactOrder(array[1], atof(array[2]), atoi(array[3]));
            makeOrder(&order, sizeOrd, walArr, trArr);
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

void makeOrder(const Order* newOrder, size_t& size, Wallet*& wallets, Transaction*& transactions) {
    if (newOrder == nullptr) {
        cout << "Order is failed...\n";
        return;
    }
    if(!walletExistInDB(newOrder->walletId, wallets, size)) {
        cout << "Wallet dont exist in DB, please try with other wallet: " << endl;
        return;
    }
    if(!(countFMICoinsInWallet(newOrder->walletId, transactions, size) >= newOrder->fmiCoins)) {
        cout << "Wallet dont have enough FMICoins. Try later :)" << endl;
        return;
    }
    cout << newOrder->walletId << endl
         << newOrder->fmiCoins << endl
         << newOrder->type << endl;
    ofstream file(ORDER_DB, std::ios::binary | std::ios::app);

    if(!file.is_open()) {
        cout << "Sorry, order not be added in DB :(" << endl;
    }
    file.write((char*)newOrder, sizeof(Order));

    if (file.good())
        cout << "Successfully done ! \n";
    else
        cout << "Error : while writing the new data! \n";

    file.close();
}

Transaction compactTransaction(Wallet& wallet, unsigned senderId) {
    Transaction tr;
    tr.time = time(0);
    tr.fmiCoins = wallet.fiatMoney / FMICoinExchangeRates;
    cout << "fmiCoins: " << tr.fmiCoins << endl;
    tr.senderId = senderId;
    tr.receiverId = wallet.id;
    return tr;
}

