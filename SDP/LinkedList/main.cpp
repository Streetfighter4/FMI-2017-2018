#include <iostream>
#include "LinkedList.h"

int main() {
    LinkedList<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(2);
    list.push_back(2);
    list.push_back(3);
    list.push_back(3);
    list.push_back(4);
    list.print();
    list.revomeRepeatedElements();
    list.print();
    return 0;
}