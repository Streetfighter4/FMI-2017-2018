//
// Created by yasen on 10/20/18.
//

#ifndef HW1_DYNAMICARRAY_HPP
#define HW1_DYNAMICARRAY_HPP


#include <cstdlib>
#include <stdexcept>
#include <iostream>

template <class T>
class DynamicArray {
    T* data;
    size_t size;
    size_t capacity;

public:
    DynamicArray();
    ~DynamicArray();
    DynamicArray(const DynamicArray<T>&) = delete;
    DynamicArray<T>& operator=(const DynamicArray<T>&) = delete;

private:
    void resize(size_t);
public:
    void push_back(const T&);

    void removeAt(size_t);

public:
    const T& operator[](size_t) const;
    T& operator[](size_t);

public:

    inline size_t getSize() const {
        return size;
    }
    inline size_t getCapacity() const {
        return capacity;
    }

public:
    void printContent() const;

};

template<class T>
DynamicArray<T>::DynamicArray() : data(new T[16]), size(0), capacity(16) {}

template<class T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template<class T>
void DynamicArray<T>::push_back(const T& elem) {
    if(size == capacity) {
        resize(static_cast<size_t>(size * 1.5));
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
void DynamicArray<T>::printContent() const {
    for (int i = 0; i < size; ++i) {
        std::cout << "Line" << i << ": " << *data[i] << std::endl;
    }
    std::cout << std::endl;
}

#endif //HW1_DYNAMICARRAY_HPP
