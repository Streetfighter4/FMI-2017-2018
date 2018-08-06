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
    size_t capacity;
    size_t size;

    void resize(size_t);

public:
    void push_back(T);
    T& pop_back();
    T pop_front();

    inline size_t getSize() const { return size; }
    inline bool isEmpty() { return size==0; }
    const T operator[](size_t) const;
    T& operator[](size_t);
public:
    explicit Conteiner(size_t newCap);
    Conteiner& operator=(const Conteiner&);
    ~Conteiner();
};

template<typename T>
void Conteiner<T>::resize(size_t newCap) {
    T* temp = data;
    data = new T[newCap];

    for (size_t i = 0; i < size; i++)
        data[i] = temp[i];

    capacity = newCap;

    delete[] temp;
}

template<typename T>
void Conteiner<T>::push_back(T element) {
    if(size >= capacity) {
        size_t newCap = (capacity == 0) ? 2 : capacity * 2;
        resize(newCap);
    }
    data[size++] = element;
}

template<typename T>
T& Conteiner<T>::pop_back() {
    if(size > 0) {
        if(size <= capacity/4) {
            resize(capacity/2);
        }
        return data[size--];
    }
}

template<typename T>
T Conteiner<T>::pop_front() {
    T element = data[0];
    T* temp = new T[size-1];
    for (int i = 0; i < size-1; ++i) {
        temp[i] = data[i+1];
    }
    delete[] data;
    data = temp;
    --size;
    return element;
}

template<typename T>
Conteiner<T>::Conteiner(size_t newCap) : capacity(newCap), size(0) {
    data = new T[capacity];
}

template<typename T>
Conteiner<T>::~Conteiner() {
    delete[] data;
}

template<typename T>
Conteiner<T>& Conteiner<T>::operator=(const Conteiner& other) {
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

template <typename T>
const T Conteiner<T>::operator[](size_t pos) const {
    if (pos >= size)
        throw std::out_of_range("invalid index");

    return data[pos];
}

template <typename T>
T& Conteiner<T>::operator[](size_t pos) {
    if (pos >= size)
        resize(pos + 1);

    return data[pos];
}

#endif //RASTERGRAPHICS_CONTEINER_H
