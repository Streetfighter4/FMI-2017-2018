//
// Created by yasen on 10/11/18.
//

#ifndef DYNAMICARRAY_DYNAMICARRAY_H
#define DYNAMICARRAY_DYNAMICARRAY_H

#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include "Helper.h"

template <class T>
class DynamicArray {
    T* data;
    size_t size;
    size_t capacity;

    bool isSorted;
public:
    DynamicArray();
    ~DynamicArray();
    DynamicArray(const DynamicArray<T>&);
    DynamicArray<T>& operator=(const DynamicArray<T>&);

private:
    void copy(const DynamicArray<T>&);
    void resize(size_t);
public:
    void push_back(const T&);
    T pop_back();

    inline bool isEmpty() const {
        return size == 0;
    }

    void insertAt(const T&, size_t);
    void removeAt(size_t);

public:
    const T& operator[](size_t) const;
    T& operator[](size_t);

    DynamicArray<T>& operator+=(DynamicArray const&);
    DynamicArray<T> operator+(DynamicArray const&) const;

public:
    T getAt(size_t) const;
    void setAt(size_t, T);

    inline size_t getSize() const {
        return size;
    }
    inline size_t getCapacity() const {
        return capacity;
    }

public:

    int search(const T&) const;

    void sort();
    void printContent() const;

};
/*
template <class T>
class DynamicArrayElementProxy {
private:
    DynamicArray<T>* pOwner;
    size_t indexOfOwner;

public:
    DynamicArrayElementProxy(DynamicArray<T>*, size_t);
    DynamicArrayElementProxy<T>& operator=(T);
    operator T() const;
};

template<class T>
DynamicArrayElementProxy<T>::DynamicArrayElementProxy(DynamicArray<T>* pDynamicArray, size_t index) :
        pOwner(pDynamicArray),
        indexOfOwner(index)
{}

template<class T>
DynamicArrayElementProxy<T>& DynamicArrayElementProxy<T>::operator=(T value) {
    pOwner->setAt(indexOfOwner, value);
    return *this;
}

template<class T>
DynamicArrayElementProxy<T>::operator T() const {
    return pOwner->getAt(indexOfOwner);
}
*/

template<class T>
DynamicArray<T>::DynamicArray() : data(new T[16]), size(0), capacity(16), isSorted(false) {}

template<class T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other) {
    if(&other != this) {
        copy(other);
    }
}

template<class T>
void DynamicArray<T>::copy(const DynamicArray<T>& other) {
    T* newData = new(std::nothrow) T[other.capacity];
    if(newData != nullptr) {
        for (int i = 0; i < other.size; ++i) {
            newData[i] = other.data[i];
        }
        size = other.size;
        capacity = other.capacity;
        isSorted = other.isSorted;

        delete[] data;
        data = newData;
    }
}

template<class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {
    if(this != &other) {
        copy(other);
    }
    return *this;
}

template<class T>
void DynamicArray<T>::push_back(const T& elem) {
    if(size == capacity) {
        resize(size*1.5);
    }
    data[size++] = elem;
}

template<class T>
void DynamicArray<T>::resize(size_t newSize) {
    T* newData = new (std::nothrow) T[newSize];
    if(newData != nullptr) {
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
}

template<class T>
T DynamicArray<T>::pop_back() {
    return data[--size];
}

template<class T>
void DynamicArray<T>::insertAt(const T& elem, size_t pos) {
    if(pos > size) {
        throw std::out_of_range("Out of range\n");
    }
    if(size == capacity) {
        resize(size*1.5);
    }
    for (int i = size; i > pos; --i) {
        data[i] = data[i-1];
    }
    data[pos] = elem;
    ++size;
}

template<class T>
void DynamicArray<T>::removeAt(size_t pos) {
    for (size_t i = pos; i < size-1; ++i) {
        data[i] = data[i+1];
    }
    if(pos < size) {
        --size;
    }
}

template<class T>
const T& DynamicArray<T>::operator[](size_t pos) const {
    if(pos >= size) {
        throw std::out_of_range("Out of range\n");
    }
    return data[pos];
}

template<class T>
T& DynamicArray<T>::operator[](size_t pos) {
    if(pos >= size) {
        throw std::out_of_range("Out of range\n");
    }
    return data[pos];
}

template<class T>
int DynamicArray<T>::search(const T& elem) const {
    int index;
    if(isSorted) {
        index = Helper::binary_search(data, size, elem);
    } else {
        index = Helper::liniar_search(data, size, elem);
    }
    return index;
}

template<class T>
void DynamicArray<T>::sort() {
    if(!isSorted) {
        Helper::insertionSort(*this, size);
        isSorted = true;
    }
}

template<class T>
void DynamicArray<T>::printContent() const {
    for (int i = 0; i < size; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

template<class T>
DynamicArray<T>& DynamicArray<T>::operator+=(DynamicArray const& other) {
    resize(size + other.size);
    for (int i = 0; i < other.size; ++i) {
        push_back(other.getAt(i));
    }
    isSorted = false;
    return *this;
}

template<class T>
DynamicArray<T> DynamicArray<T>::operator+(DynamicArray const& other) const {
    DynamicArray<T> temp;
    temp.resize(size + other.size);
    temp += *this;
    temp += other;
    return temp;
}

template<class T>
T DynamicArray<T>::getAt(size_t index) const {
    if(index >= size) {
        throw std::out_of_range("Out of range\n");
    }
    return data[index];
}

template<class T>
void DynamicArray<T>::setAt(size_t index, T elem) {
    if(index >= size) {
        throw std::out_of_range("Out of range\n");
    }
    data[index] = elem;
}


#endif //DYNAMICARRAY_DYNAMICARRAY_H
