//
// Created by yasen on 3/20/18.
//

#include "Helpers.h"
#include "Constants.h"
#include "Wallets.h"
#include "Transactions.h"
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


