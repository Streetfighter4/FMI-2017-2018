#include <iostream>
#include "BinaryTree.h"
#include "MaxHeap.hpp"



int main() {
    BinaryTree<int> toni;
    const int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};


    BinaryTree<int> yasen;
    yasen.makebalanceTreeFromSortedArray((const int *&) array, 10);
    yasen.print();
    delete[] array;
    return 0;
}