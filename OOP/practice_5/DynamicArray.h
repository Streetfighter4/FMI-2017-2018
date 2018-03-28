//
// Created by yasen on 3/28/18.
//

#ifndef PRACTICE_5_DYNAMICARRAY_H
#define PRACTICE_5_DYNAMICARRAY_H

#include <iostream>
using std::cout;
using std::endl;

class DynamicArray {
    int* array;
    size_t size;
    size_t capacity;
    void resize();
public:

    DynamicArray();
    DynamicArray(size_t newCapacity);
    ~DynamicArray();

    void pushBack(int element);
    void removedAt(int index);
    int getAt(int index);
    void setAt(int index, int value);
    void printInfo();
};


#endif //PRACTICE_5_DYNAMICARRAY_H
