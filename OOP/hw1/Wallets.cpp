//
// Created by yasen on 3/19/18.
//
#include "Wallets.h"
#include "Transactions.h"
#include "Constants.h"
#include <fstream>
#include <string.h>

using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::ifstream;

unsigned maxCurrId(Wallet*& wallets, size_t size) {
    if (wallets != nullptr)
        delete[] wallets;

    unsigned maxId = 0;
    for (int i = 0; i < size; ++i) {
        cout << "wallets[i].id: " << wallets[i].id << endl;
        if(wallets[i].id > maxId)
            maxId = wallets[i].id;
    }
    
    cout << "maxId: " << maxId << endl;
    return maxId;
}

void addWalletInDB(Wallet* newWallet, size_t& size) {

    if (newWallet == nullptr) {
        cout << "nothing to save..." << endl;
        return;
    }
    cout << newWallet->id << " " << newWallet->fiatMoney << " " << newWallet->owner << endl;
    ofstream file(WALLETS_DB, std::ios::binary | std::ios::app);

    if(!file.is_open()) {
        cout << "Sorry, wallet not be added in DB :(" << endl;
    }
    file.write((char*)newWallet, sizeof(Wallet));

    if (file.good())
        cout << "successfully done !" << endl;
    else
        cout << "error : while writing the new data!" << endl;
    size++;
    file.close();
}

void writeWalletsInFileDB(const Wallet* wallets, size_t size) {
    if (wallets == nullptr || size == 0) {
        cout << "nothing to save..." << endl;
        return;
    }

    ofstream fileDB(WALLETS_DB, std::ios::binary);

    if (!fileDB.is_open()) {
        cout << "error : can't open the database for writing !" << endl;
        return;
    }

    //writing the updated info
    fileDB.write((char*)wallets, sizeof(Wallet)*size);

    if (fileDB.good())
        cout << "successfully done !" << endl;
    else
        cout << "error : while writing the new data!" << endl;

    fileDB.close();
}

size_t readWalletsFromFileDB(Wallet*& wallets){

    if (wallets != nullptr)
        delete[] wallets;

    ifstream fileDB(WALLETS_DB, std::ios::binary);

    if (!fileDB.is_open()) {

        cout << "error : can't open the database !" << endl;
        wallets = nullptr;
        return 0;
    }

    //the length of the file in bytes
    size_t len = 0;

    fileDB.seekg(0, std::ios::end);
    len = fileDB.tellg();
    fileDB.seekg(0, std::ios::beg);

    size_t walCnt = len / sizeof(Wallet);

    if (walCnt == 0) {

        cout << "Empty data base!" << endl;
        return 0;
    }

    //allocating memory for all students
    wallets = new (std::nothrow) Wallet[walCnt];

    if (wallets == nullptr) {

        cout << "Cannot allocate memory!" << endl;
        return 0;
    }

    //reading them
    fileDB.read((char*)wallets, sizeof(Wallet)*walCnt);

    if (!fileDB.good()) {

        cout << "error : while reading the database!" << endl;
        delete[] wallets;
        wallets = nullptr;
        return 0;
    }

    cout << "successfully loaded the data base!" << endl;

    fileDB.close();
    return walCnt;
}

bool walletExistInDB(unsigned walletId, Wallet*& wallets, size_t size) {
    cout << "Size of wallets.dat: " << size << endl;
    for (int j = 0; j < size; ++j) {
        cout << wallets[j].id << wallets[j].fiatMoney << wallets[j].owner << endl;
    }
    for (int i = 0; i < size; ++i) {
        cout << "wallets[i].id: " << wallets[i].id << " - walletId: " << walletId << endl;
        if(wallets[i].id == walletId)
            return true;
    }
    return false;
}

Wallet compactWallet(unsigned curr_max_id, double money, char* name) {
    Wallet wallet;
    wallet.id = ++curr_max_id;
    wallet.fiatMoney = money;
    strcpy(wallet.owner,name);
    return wallet;
}

