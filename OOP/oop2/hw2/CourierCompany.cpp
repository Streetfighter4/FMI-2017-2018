//
// Created by yasen on 4/26/19.
//

#include "CourierCompany.h"

void CourierCompany::clean() {
    for (int i = 0; i < size; ++i) {
        delete items[i];
    }
    delete[] items;
    items = nullptr;
    size = 0;
}

void CourierCompany::resize(size_t newCapacity) {
    Item** temp = new Item*[newCapacity];

    for (int i = 0; i < size; ++i) {
        temp[i] = items[i];
    }
    delete[] items;
    items = temp;
    capacity = newCapacity;
}

CourierCompany::CourierCompany(size_t newCapacity) : size(0), capacity(newCapacity), allCostForTransport(0.0), allVolume(0) {
    items = new Item*[capacity];
}

CourierCompany::~CourierCompany() {
    clean();
}

void CourierCompany::addItem(Item* item) {
    if(size == capacity) {
        resize(capacity*2);
    }
    items[size++] = item;
    allCostForTransport += item->costForTransport();
    allVolume += item->getAllWeight();
}

double CourierCompany::getAllCostForTransport() const {
    return allCostForTransport;
}

size_t CourierCompany::getAllVolume() const {
    return allVolume;
}

void CourierCompany::print() const {
    std::cout << "Company has " << size << " items and capacity: " << capacity << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << "Item " << i+1 << ':' << std::endl;
        items[i]->print();
        std::cout << std::endl;
    }
}

