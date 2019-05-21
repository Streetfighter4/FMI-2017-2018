//
// Created by yasen on 4/20/19.
//

#ifndef HW2_ITEM_H
#define HW2_ITEM_H


#include <cstddef>
#include <fstream>
#include "Element.h"
#include "Box.h"

class Item {

protected:
    char* address;
    double costPerKilogram;
    Box box;
    size_t capacity;

    size_t size;
    Element** list;
    size_t allWeight;
protected:
    virtual void clean();
    virtual void copy(const Item& other);
    void resize(size_t newCapacity);
public:
    Item();
    Item(const char* newAddress, double newCostPerKilogram, size_t newCapacity, const Box& newBox);
    Item(const Item& other);
    Item&operator=(const Item& rhs);
    virtual ~Item();

public:
    void add_element(Element* elem);
    inline size_t getAllWeight() const { return allWeight; }
    virtual inline double costForTransport() const { return allWeight*costPerKilogram; }

    void printElements() const;
    virtual void print() const;
    virtual Item* clone();

    void serialize(const char* fileName) const;
};


#endif //HW2_ITEM_H
