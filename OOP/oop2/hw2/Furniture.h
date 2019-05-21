//
// Created by yasen on 4/22/19.
//

#ifndef HW2_FURNITURE_H
#define HW2_FURNITURE_H


#include "Item.h"

class Furniture : public Item {
    char* brand;

private:
    void clean() override;
    void copy(const Furniture& other);
public:
    Furniture(const char* newAddress, double newCostPerKilogram, size_t newCapacity, const Box& newBox, const char* newBrand);
    Furniture(const Furniture& other);
    Furniture&operator=(const Furniture& rhs);
    ~Furniture() override;

public:
    inline size_t getWeight() const { return allWeight; }
    bool isBreakable() const;
    double costForTransport() const override;

    Item* clone() override;
};


#endif //HW2_FURNITURE_H
