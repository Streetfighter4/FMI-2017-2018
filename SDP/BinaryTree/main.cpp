#include <iostream>
#include "BinaryTree.h"
#include "MaxHeap.hpp"

int main() {
    BinaryTree<int> toni;

    toni.insert(4);
    toni.insert(5);
    toni.insert(6);
    toni.insert(11);
    toni.insert(19);
    toni.insert(8);
    toni.insert(10);
    toni.insert(17);
    toni.insert(43);
    toni.insert(31);
    toni.insert(49);
    toni.print();
    std::cout << std::endl;

    std::cout << std::endl;
    BinaryTree<int> yasen;
    yasen = toni;
    yasen.print();

    return 0;
}