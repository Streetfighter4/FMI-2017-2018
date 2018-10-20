//
// Created by yasen on 10/17/18.
//

#ifndef LINKEDLIST_LINKEDLIST_H
#define LINKEDLIST_LINKEDLIST_H

#include <cstdlib>
#include <iostream>
#include <stdexcept>

template <class T>
class LinkedList {
    class Node {
    public:
        Node* pNext;
        T data;

        Node() = delete;
        Node(Node* nextNode, T nextData) : pNext(nextNode), data(nextData) {}
    };

    Node* head;
    Node* tail;

    size_t size;
public:
    LinkedList();
    LinkedList(const LinkedList<T>&);
    LinkedList<T>& operator=(const LinkedList<T>&);
    ~LinkedList();

private:
    void copy(const LinkedList<T>&);
    void clean();
public:
    void push_front(const T&);
    void pop_front();

    void push_back(const T&);
    void pop_back();

    void insertAt(size_t, const T&);
    void removeAt(size_t);

public:
    inline T& front() {
        return head->data;
    }
    inline const T& front() const {
        return head->data;
    }
    inline T& back() {
        return tail->data;
    }
    inline const T& back() const {
        return tail->data;
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

    void print();

};

template<class T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), size(0) {}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) {
    copy(other);
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T>& other) {
    if(this != &other) {
        clean();
        copy(other);
    }
    return *this;
}


template<class T>
LinkedList<T>::~LinkedList() {
    clean();
}

template<class T>
void LinkedList<T>::copy(const LinkedList<T>& other) {
    if(other.isEmpty()) {
        return;
    }
    try{
        head = new Node(other.head->data);
        Node* ToCopy = other.head;
        Node* copier = head;

        while (ToCopy->pNext != nullptr) {

            ToCopy = ToCopy->pNext;

            copier->pNext = new Node(ToCopy->data);
            copier = copier->pNext;

        }

        tail = copier;
    } catch(std::bad_alloc&) {
        clean();
        throw;
    }
    size = other.size;
}

template<class T>
void LinkedList<T>::clean() {
    Node* destroyer;
    while(head != nullptr) {
        destroyer = head;
        head = head->pNext;
        delete destroyer;
    }

    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<class T>
void LinkedList<T>::print() {
    Node* ptr = head;
    while(ptr->pNext != nullptr) {
        std::cout << ptr->data << ' ';
        ptr = ptr->pNext;
    }
    std::cout << ptr->data;
    std::cout << std::endl;
}

template<class T>
void LinkedList<T>::push_front(const T& newData) {
    Node* newNode;
    if(size == 0) {
        newNode = new Node(nullptr, newData);
        tail = newNode;
    } else {
        newNode = new Node(head, newData);
    }
    head = newNode;
    ++size;
}

template<class T>
void LinkedList<T>::pop_front() {
    if(size == 0) {
        throw std::runtime_error("the list is empty!\n");
    }
    Node* temp = head;
    head = head->pNext;
    delete temp;
    --size;
}

template<class T>
void LinkedList<T>::push_back(const T& newData) {
    Node* newNode = new Node(nullptr, newData);
    if(size == 0) {
        head = newNode;
    } else {
        tail->pNext = newNode;
    }
    tail = newNode;
    ++size;
}

template<class T>
void LinkedList<T>::pop_back() {
    if(size == 0) {
        throw std::runtime_error("the list is empty!\n");
    }
    if(size == 1) {
        delete head;
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    Node* destroyer = head;
    while(destroyer->pNext != tail) {
        destroyer = destroyer->pNext;
    }
    delete tail;
    tail = destroyer;
    tail->pNext = nullptr;
    --size;
}

template<class T>
void LinkedList<T>::insertAt(size_t index, const T& newData) {
    if(index > size) {
        throw std::out_of_range("invalid index!\n");
    }
    if(index == 0) {
        push_front(newData);
        return;
    }
    if(index == size) {
        push_back(newData);
        return;
    }

    Node* insertAfter = head;
    for (int i = 0; i < index-1; ++i) {
        insertAfter = insertAfter->pNext;
    }
    try{
        Node* newNode = new Node(insertAfter->pNext, newData);
        insertAfter->pNext = newNode;
    } catch (std::bad_alloc& e) {
        std::cout << e.what() << std::endl;
        throw;
    }
}

template<class T>
void LinkedList<T>::removeAt(size_t index) {
    if(index > size) {
        throw std::out_of_range("invalid index!\n");
    }
    if(index == 0) {
        pop_front();
        return;
    }
    if(index == size) {
        pop_back();
        return;
    }

    Node* deleteAfter = head;
    for (int i = 0; i < index-1; ++i) {
        deleteAfter = deleteAfter->pNext;
    }
    try{
        Node* temp = deleteAfter->pNext->pNext;
        delete deleteAfter->pNext;
        deleteAfter->pNext = temp;
    } catch (std::bad_alloc& e) {
        std::cout << e.what() << std::endl;
        throw;
    }

}

template<class T>
void LinkedList<T>::reverse() {
    if(size == 0 || size == 1) {
        return;
    }
    if(size == 2) {
        tail = head;
        head = head->pNext;
        return;
    }

}


#endif //LINKEDLIST_LINKEDLIST_H
