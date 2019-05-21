//
// Created by yasen on 4/25/19.
//

#ifndef HW2_SHOES_H
#define HW2_SHOES_H


#include "Item.h"

class Shoes : public Item {
    bool canMeasuredOnDelivery;
private:
    void clean() override;
    void copy(const Shoes& rhs);
public:
    Shoes();
    Shoes(const char* newAddress, double newCostPerKilogram, size_t newCapacity, const Box& newBox, bool newCanMeasuredOnDelivery = false);
    Shoes(const Shoes& other);
    Shoes&operator=(const Shoes& rhs);
    ~Shoes() override;

public:
    double costForTransport() const override;
    void print() const override;

    Item* clone() override;
};


#endif //HW2_SHOES_H
