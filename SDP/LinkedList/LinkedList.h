//
// Created by yasen on 10/17/18.
//

#ifndef LINKEDLIST_LINKEDLIST_H
#define LINKEDLIST_LINKEDLIST_H

#include <cstdlib>

template <class T>
class LinkedList {
    class Node {
    public:
        Node* pNext;
        T* data;
    };

    Node* head;
    Node* tail;

    size_t size;
public:
    LinkedList();
    LinkedList(const LinkedList<T>&) = delete;
    LinkedList<T>& operator=(const LinkedList<T>&);
    ~LinkedList();

private:
    void copy(const LinkedList<T>&);

public:
    void push_front(const T&);
    void pop_front();

    void push_back(const T&);
    void pop_back();

    void insertAt(size_t, const T&);
    void removeAt(size_t);

public:
    inline T& front() {
        return *(head->data);
    }
    inline const T& front() const {
        return *(head->data);
    }
    inline T& back() {
        return *(tail->data);
    }
    inline const T& back() const {
        return *(tail->data);
    }

public:
    void reverse();

public:
    inline size_t getSize() const {
        return size;
    }
    inline bool isEmpty() const {
        return size == 0;
    }
};

template<class T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), size(0) {}

template<class T>
void LinkedList<T>::copy(const LinkedList<T>& other) {

}

template<class T>
void LinkedList<T>::push_front(const T& newNode) {

}


#endif //LINKEDLIST_LINKEDLIST_H
