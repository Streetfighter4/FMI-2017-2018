//
// Created by yasen on 4/22/19.
//

#include "Furniture.h"

void Furniture::clean() {
    Item::clean();
    delete[] brand;
}

void Furniture::copy(const Furniture& other) {
    brand = new char[strlen(other.brand)+1];
    if(brand) {
        clean();
        strcpy(brand, other.brand);
        Item::copy(other);
    }
}

Furniture::Furniture(const char* newAddress, double newCostPerKilogram, size_t newCapacity, const Box& newBox,
                     const char* newBrand) : Item(newAddress, newCostPerKilogram, newCapacity, newBox) {
    brand = new char[strlen(newBrand)+1];
    if(brand) {
        strcpy(brand, newBrand);
    }
}

Furniture::Furniture(const Furniture& other) {
    clean();
    copy(other);
}

Furniture& Furniture::operator=(const Furniture& rhs) {
    if(this != &rhs) {
        clean();
        copy(rhs);
    }
    return *this;
}

Furniture::~Furniture() {
    clean();
}

double Furniture::costForTransport() const {
    if(isBreakable()) {
        return Item::costForTransport() * 1.5;
    }
    return costForTransport();
}

bool Furniture::isBreakable() const {
    for (int i = 0; i < size; ++i) {
        if(list[i]->isBreakable())
            return true;
    }
    return false;
}

Item* Furniture::clone() {
    return new Furniture(*this);
}

