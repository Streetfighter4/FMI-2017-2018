#include <iostream>

#include "DynamicArray.h"
int main() {
    DynamicArray arr;
    arr.pushBack(4);
    arr.setAt(5, 2);
    arr.printInfo();
    for (int i = 0; i < 20; ++i) {
        arr.pushBack(i);
    }
    arr.removedAt(21);
    cout << arr.getAt(19) << endl;
    arr.printInfo();
    return 0;
}