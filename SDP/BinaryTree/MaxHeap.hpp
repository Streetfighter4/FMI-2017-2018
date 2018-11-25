//
// Created by yasen on 11/19/18.
//

#ifndef BINARYTREE_MAXHEAP_HPP
#define BINARYTREE_MAXHEAP_HPP


#include <cstdlib>
#include <algorithm>
#include <iostream>

template <typename T>
class MaxHeap {
    T* data;
    size_t size;
    size_t capacity;
public:
    MaxHeap();
    ~MaxHeap();
public:
    void insert(const T&);
    void remove(const T&);
    void print();
private:
    void resize(size_t);
    void balance();
};

template<typename T>
MaxHeap<T>::MaxHeap() : data(new T[3]), size(0), capacity(3){}

template<typename T>
MaxHeap<T>::~MaxHeap() {
    delete[] data;
}

template<typename T>
void MaxHeap<T>::resize(size_t newSize) {
    T* newData = new T[newSize];
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newSize;
}

template<typename T>
void MaxHeap<T>::insert(const T& elem) {
    if(size == capacity) {
        resize(capacity*2);
    }
    data[size++] = elem;
    if(size > 1) {
        balance();
    }
}

template<typename T>
void MaxHeap<T>::balance() {
    size_t currentIndex = size-1;

    while (data[currentIndex] > data[(currentIndex-1)/2] && currentIndex > 0) {
        std::swap(data[currentIndex], data[(currentIndex-1)/2]);
        currentIndex = (currentIndex-1)/2;
    }
}

template<typename T>
void MaxHeap<T>::print() {
    for (int i = 0; i < size; ++i) {
        std::cout << data[i] << std::endl;
    }
}

template<typename T>
void MaxHeap<T>::remove(const T& elem) {
    for (int i = 0; i < size; ++i) {
        if(data[i] == elem) {
            std::swap(data[i], data[0]);
        }
    }
}


#endif //BINARYTREE_MAXHEAP_HPP
