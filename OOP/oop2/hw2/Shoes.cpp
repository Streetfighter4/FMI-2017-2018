//
// Created by yasen on 4/25/19.
//

#include "Shoes.h"

void Shoes::clean() {
    Item::clean();
}

void Shoes::copy(const Shoes& rhs) {
    Item::copy(rhs);
    canMeasuredOnDelivery = rhs.canMeasuredOnDelivery;
}

Shoes::Shoes() : Item(), canMeasuredOnDelivery(false) {}

Shoes::Shoes(const char *newAddress, double newCostPerKilogram, size_t newCapacity, const Box &newBox,
             bool newCanMeasuredOnDelivery) : Item(newAddress, newCostPerKilogram, newCapacity, newBox) ,
                canMeasuredOnDelivery(newCanMeasuredOnDelivery){}

Shoes::Shoes(const Shoes& other) {
    clean();
    copy(other);
}

Shoes& Shoes::operator=(const Shoes& rhs) {
    if(this != &rhs) {
        clean();
        copy(rhs);
    }
    return *this;
}

Shoes::~Shoes() {
    clean();
}

double Shoes::costForTransport() const {
    if(canMeasuredOnDelivery) {
        return Item::costForTransport() * 0.03;
    }
    return Item::costForTransport();
}

void Shoes::print() const {
    Item::print();
    if(canMeasuredOnDelivery) {
        std::cout << "Can be measure in delivery" << std::endl;
    } else {
        std::cout << "Can't be measure in delivery" << std::endl;
    }
}

Item* Shoes::clone() {
    return new Shoes(*this);
}
