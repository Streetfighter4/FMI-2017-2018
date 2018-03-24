//
// Created by yasen on 3/24/18.
//

#include "Orders.h"
#include "Wallets.h"
#include "Constants.h"

#include <fstream>
#include <string.h>
using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::atof;


size_t readOrderFromFileDB(Order*& orders) {

    if (orders != nullptr)
        delete[] orders;

    std::ifstream fileDB(ORDER_DB, std::ios::binary);

    if (!fileDB.is_open()) {

        std::cout << "Error : can't open the database !\n";
        orders = nullptr;
        return 0;
    }


    //the length of the file in bytes
    size_t len = 0;

    fileDB.seekg(0, std::ios::end);
    len = fileDB.tellg();
    fileDB.seekg(0, std::ios::beg);

    size_t ordCnt = len / sizeof(Order);

    if (ordCnt == 0) {

        std::cout << "Empty data base!\n";
        return 0;
    }


    //allocating memory for all students
    orders = new (std::nothrow) Order[ordCnt];

    if (orders == nullptr) {

        std::cout << "Cannot allocate memory!\n";
        return 0;
    }

    //reading them
    fileDB.read((char*)orders, sizeof(Order)*ordCnt);

    if (!fileDB.good()) {
        std::cout << "Error : while reading the database! \n";
        delete[] orders;
        orders = nullptr;
        return 0;
    }

    std::cout << "Successfully loaded the transactions!\n";

    fileDB.close();
    return ordCnt;
}


Order compactOrder(char* type, double fmiCoin, unsigned walletId) {
    Order order;
    order.fmiCoins = fmiCoin;
    order.walletId = walletId;
    if (!strcmp(type, "sell"))
        order.type = order.SELL;
    else if(!strcmp(type, "buy"))
        order.type = order.BUY;
    return order;
}

void writeOrdersInFileDB(const Order* orders, size_t size) {
    if (orders == nullptr || size == 0) {
        cout << "nothing to save..." << endl;
        return;
    }

    ofstream fileDB(ORDER_DB, std::ios::binary);

    if (!fileDB.is_open()) {
        cout << "error : can't open the database for writing !" << endl;
        return;
    }

    //writing the updated info
    fileDB.write((char*)orders, sizeof(Order)*size);

    if (fileDB.good())
        cout << "successfully done !" << endl;
    else
        cout << "error : while writing the new data!" << endl;

    fileDB.close();
}

