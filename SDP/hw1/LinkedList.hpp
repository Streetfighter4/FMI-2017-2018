//
// Created by yasen on 10/20/18.
//


#ifndef HW1_LINKEDLIST_HPP
#define HW1_LINKEDLIST_HPP

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
        Node(Node* nextNode, const T newData){
            pNext = nextNode;
            data = newData;
        }
    };

    Node* head;
    Node* tail;

    size_t size{};
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

    void mergeWith(LinkedList<T>&);

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
    inline size_t getSize() const {
        return size;
    }
    inline bool isEmpty() const {
        return size == 0;
    }

    int search(T) const;

    LinkedList<T>* splitBy(size_t index);

    friend std::ostream& operator<<(std::ostream &os, const LinkedList& obj) {
        Node* ptr = obj.head;
        while(ptr->pNext != nullptr) {
            os << *ptr->data << " - ";
            ptr = ptr->pNext;
        }
        os << *ptr->data;
        os << std::endl;

        return os;
    }
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
        head = new Node(nullptr, other.head->data);
        Node* ToCopy = other.head;
        Node* copier = head;

        while (ToCopy->pNext != nullptr) {

            ToCopy = ToCopy->pNext;

            copier->pNext = new Node(nullptr, ToCopy->data);
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
int LinkedList<T>::search(const T obj) const {
    Node* ptr = head;
    int index = 0;
    while(ptr != nullptr) {
        if(*ptr->data == *obj) {
            return index;
        }
        ++index;
        ptr = ptr->pNext;
    }

    return -1;
}

template<class T>
LinkedList<T> *LinkedList<T>::splitBy(size_t index) {
    LinkedList<T>* newQ = new LinkedList<T>;
    Node* temp = head;
    for (int i = 0; i < index - 1; ++i) {
        temp = temp->pNext;
    }
    newQ->head = temp->pNext->pNext;
    delete temp->pNext;
    temp->pNext = nullptr;
    newQ->tail = tail;
    tail = temp;

    return newQ;
}

template<class T>
void LinkedList<T>::mergeWith(LinkedList<T>& rhs) {
    tail->pNext = rhs.head;
    tail = rhs.tail;
    size+=rhs.size;
    rhs.head = rhs.tail = nullptr;
    rhs.size = 0;
}


#endif //HW1_LINKEDLIST_HPP
