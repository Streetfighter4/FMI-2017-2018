#include <iostream>
#include "LinkedList.h"

int main() {
    LinkedList<int> list;

    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.print();
    list.insertAt(2, 37);
    list.print();
    list.removeAt(3);
    list.print();
    std::cout << list.front() << std::endl;
    std::cout << list.back() << std::endl;
    return 0;
}