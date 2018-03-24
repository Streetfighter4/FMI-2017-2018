//
// Created by yasen on 3/24/18.
//
#include "Transactions.h"
#include "Constants.h"
using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::atof;

size_t readTransactionsFromFileDB(Transaction*& transactions) {

    if (transactions != nullptr)
        delete[] transactions;

    std::ifstream fileDB(TRANSACTIONS_DB, std::ios::binary);

    if (!fileDB.is_open()) {

        std::cout << "error : can't open the database !\n";
        transactions = nullptr;
        return 0;
    }

    //the length of the file in bytes
    size_t len = 0;

    fileDB.seekg(0, std::ios::end);
    len = fileDB.tellg();
    fileDB.seekg(0, std::ios::beg);

    size_t trCnt = len / sizeof(Transaction);

    if (trCnt == 0) {

        std::cout << "Empty data base!\n";
        return 0;
    }


    //allocating memory for all students
    transactions = new (std::nothrow) Transaction[trCnt];

    if (transactions == nullptr) {

        std::cout << "Cannot allocate memory!\n";
        return 0;
    }

    //reading them
    fileDB.read((char*)transactions, sizeof(Transaction)*trCnt);

    if (!fileDB.good()) {

        std::cout << "error : while reading the database! \n";
        delete[] transactions;
        transactions = nullptr;
        return 0;
    }

    std::cout << "Successfully loaded the transactions!\n";

    fileDB.close();
    return trCnt;
}

void makeTransaction(const Transaction* newTransaction, size_t& size) {
    if (newTransaction == nullptr) {

        std::cout << "nothing to save...\n";
        return;
    }
    cout << newTransaction->receiverId << endl
         << newTransaction->senderId << endl
         << newTransaction->fmiCoins << endl
                                      << newTransaction->time << endl;
    ofstream file(TRANSACTIONS_DB, std::ios::binary | std::ios::app);

    if(!file.is_open()) {
        cout << "Sorry, wallet not be added in DB :(" << endl;
    }
    file.write((char*)newTransaction, sizeof(Transaction));

    if (file.good())
        std::cout << "Successfully done ! \n";
    else
        std::cout << "Error : while writing the new data! \n";
    size++;
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

void writeTransactiosInFileDB(const Transaction* transactions, size_t size) {
    if (transactions == nullptr || size == 0) {
        cout << "nothing to save..." << endl;
        return;
    }

    ofstream fileDB(TRANSACTIONS_DB, std::ios::binary);

    if (!fileDB.is_open()) {
        cout << "error : can't open the database for writing !" << endl;
        return;
    }

    //writing the updated info
    fileDB.write((char*)transactions, sizeof(Transaction)*size);

    if (fileDB.good())
        cout << "Successfully done !" << endl;
    else
        cout << "Error : while writing the new data!" << endl;

    fileDB.close();
}

