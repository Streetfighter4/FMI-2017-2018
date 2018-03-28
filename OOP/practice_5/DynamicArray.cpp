//
// Created by yasen on 3/28/18.
//

#include "DynamicArray.h"
const int initialCapacity = 16;

DynamicArray::DynamicArray() : capacity(initialCapacity), size(0) {
    array = new int[capacity];
}

DynamicArray::DynamicArray(size_t newCapacity) : size(0), capacity(newCapacity) {
    array = new int[capacity];
}

DynamicArray::~DynamicArray() {
    delete[] array;
}

void DynamicArray::resize() {
    int newCapacity = capacity*2;
    int* newArr = new int[newCapacity];
    for (int i = 0; i < capacity; ++i) {
        newArr[i] = array[i];
    }
    capacity = newCapacity;
    delete[] array;
    array = newArr;
}

void DynamicArray::pushBack(int element) {
    if(size == capacity) {
        resize();
    }
    array[size] = element;
    ++size;
}

void swap(int& a, int& b) {
    int buff = a;
    a = b;
    b = buff;
}

void DynamicArray::removedAt(int index) {
    swap(array[index], array[size]);
    --size;
}
int DynamicArray::getAt(int index) {
    if(index < size) {
        return array[index];
    } else {
        std::cout << "Invalid index of array" << std::endl;
        return  -1;
    }
}
void DynamicArray::setAt(int index, int value) {
    if(index >= size && index < capacity) {
        pushBack(value);
    } else if (index < size) {
        array[index] = value;
    }
}

void DynamicArray::printInfo() {
    cout << "Address: " << this << endl <<
            "Size: " << size << endl <<
            "Capacity: " << capacity << endl;
}
