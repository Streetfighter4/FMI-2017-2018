//
// Created by yasen on 6/26/18.
//

#ifndef RASTERGRAPHICS_CONTEINER_H
#define RASTERGRAPHICS_CONTEINER_H


#include <cstdlib>
#include <stdexcept>

template <typename T>
class Conteiner {
    T* data;
    size_t size;
    size_t capacity;

    void resize(size_t);

public:
    inline size_t getSize() const { return size; }
    inline bool isEmpty() const { return size == 0; }

    void push_back(T element );
    T& pop_back();
    T& pop_front();

    const T operator[](size_t) const;
    T&operator[](size_t);
public:
    explicit Conteiner(size_t);
    Conteiner<T>&operator=(const Conteiner<T>& other);
    ~Conteiner();
};

template<typename T>
void Conteiner<T>::resize(size_t newCap) {
    T* temp = data;
    data = new T[newCap];

    if(data) {
        for (int i = 0; i < size; ++i) {
            data[i] = temp[i];
        }
        capacity = newCap;
        delete[] temp;
    }
}

template<typename T>
void Conteiner<T>::push_back(T element) {
    if(size >= capacity) {
        size_t newCap = (capacity == 0) ? 2 : capacity*2;
        resize(newCap);
    }
    data[size++] = element;
}

template<typename T>
T &Conteiner<T>::pop_back() {
    T element;
    if(size > 0) {
        element = data[size--];
        if(size <= capacity/4) {
            resize(capacity/2);
        }
    }

    return element;
}

template<typename T>
T &Conteiner<T>::pop_front() {
    T element;
    if(size > 0) {
        element = data[0];
        for (int i = 0; i < size-1; ++i) {
            data[i] = data[i+1];
        }
        if(size <= capacity/4) {
            resize(capacity/2);
        }
    }

    return element;
}

template<typename T>
const T Conteiner<T>::operator[](size_t pos) const {
    if(size >= pos) {
        throw std::out_of_range("out of range");
    }
    return data[pos];
}

template<typename T>
T &Conteiner<T>::operator[](size_t pos) {
    if(pos >= size) {
        resize(pos+1);
    }
    return data[pos];
}

template<typename T>
Conteiner<T>::Conteiner(size_t newCap) : size(0), capacity(newCap), data(new T[capacity]) {}

template<typename T>
Conteiner<T>& Conteiner<T>::operator=(const Conteiner<T>& other) {
    if(this != &other) {
        delete[] data;
        data = new T[other.capacity];

        for (int i = 0; i < other.size; ++i) {
            data[i] = other.data[i];
        }

        size = other.size;
        capacity = other.capacity;
    }
    return *this;
}

template<typename T>
Conteiner<T>::~Conteiner() {
    delete[] data;
}


#endif //RASTERGRAPHICS_CONTEINER_H
