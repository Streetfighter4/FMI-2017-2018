//
// Created by yasen on 6/26/18.
//

#ifndef RASTERGRAPHICS_COMMANDCONTEINER_H
#define RASTERGRAPHICS_COMMANDCONTEINER_H


#include <stdlib.h>

template <typename T>
class CommandConteiner {
    T* data;
    size_t capacity;
    size_t size;

    void resize(size_t);

public:
    void push_back(T&);
    T& pop_back();
    T& pop_front();

public:
    CommandConteiner();
    ~CommandConteiner();
};

template<typename T>
void CommandConteiner<T>::resize(size_t newCap) {
    T* temp = data;
    data = new T[newCap];

    for (size_t i = 0; i < size; i++)
        data[i] = temp[i];

    capacity = newCap;

    delete[] temp;
}

template<typename T>
void CommandConteiner<T>::push_back(T& command) {
    if(size >= capacity) {
        size_t newCap = (capacity == 0) ? 2 : capacity * 2;
        resize(newCap);
    }
    data[size++] = command;
}

template<typename T>
T& CommandConteiner<T>::pop_back() {
    if(size > 0) {
        T command = data[size--];
        if(size <= capacity/4) {
            resize(capacity/2);
        }
        return command;
    } else {
        return nullptr;
    }
}

template<typename T>
T& CommandConteiner<T>::pop_front() {
    T command = data[0];
    --size;
    if(size <= capacity/4) {
        resize(capacity/2);
    }
    return command;
}

template<typename T>
CommandConteiner<T>::CommandConteiner() : data(nullptr), capacity(2), size(0) {}

template<typename T>
CommandConteiner<T>::~CommandConteiner() {
    for (int i = 0; i < size; ++i) {
        delete data[i];
    }
    delete[] data;
}


#endif //RASTERGRAPHICS_COMMANDCONTEINER_H
