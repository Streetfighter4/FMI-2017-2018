//
// Created by yasen on 4/20/19.
//

#include "Item.h"

void Item::clean() {
    delete[] address;
    address = nullptr;
    for (int i = 0; i < size; ++i) {
        delete list[i];
    }
    delete[] list;
    list = nullptr;
    size = 0;
}

void Item::copy(const Item& other) {
    list = new Element*[other.size];

    for (int i = 0; i < other.size; ++i) {
        list[i] = new Element(*other.list[i]);
    }

    address = new (std::nothrow) char[strlen(other.address) + 1];
    if(address != nullptr) {
        strcpy(address, other.address);
    }

    costPerKilogram = other.costPerKilogram;
    size = other.size;
    capacity = other.capacity;
    allWeight = other.allWeight;
}

void Item::resize(size_t newCapacity) {
    Element** temp = new Element*[newCapacity];
    for (int i = 0; i < size; ++i) {
        temp[i] = list[i];
    }
    delete[] list;
    list = temp;
    capacity = newCapacity;
}

Item::Item() : address(nullptr), costPerKilogram(0.0), size(0), capacity(0), list(nullptr), allWeight(0) {}

Item::Item(const char* newAddress, double newCostPerKilogram, size_t newCapacity, const Box& newBox) : box(newBox) {
    allWeight = 0;
    size = 0;
    capacity = newCapacity;
    costPerKilogram = newCostPerKilogram;
    list = new Element*[capacity];
    address = new char[strlen(newAddress) + 1];

    if(address != nullptr) {
        strcpy(address, newAddress);
    }
}

Item::Item(const Item& other) {
    copy(other);
}

Item& Item::operator=(const Item& rhs) {
    if(this != &rhs) {
        clean();
        copy(rhs);
    }
    return *this;
}

Item::~Item() {
    clean();
}

void Item::add_element(Element* elem) {
    if(size == capacity) {
        resize(capacity*2);
    }

    list[size++] = new Element(*elem);
    allWeight += elem->getWeight();
}

void Item::printElements() const {
    std::cout << "Element list: " << std::endl;
    for (int i = 0; i < size; ++i) {
        list[i]->print();
    }
}

void Item::print() const {
    std::cout << "Size: " << size << std::endl;
    std::cout << "Address: " << address << std::endl;
    std::cout << "All weight: " << allWeight << std::endl;
    std::cout << "Cost per kilogram: " << costPerKilogram << std::endl;
    std::cout << "Box with volume: " << box.getVolume() << std::endl;
    printElements();
}

void Item::serialize(const char* fileName) const {
    std::ofstream ofs(fileName);

    if(!ofs.is_open()) {
        std::cout << "File is not open!" << std::endl;
        return;
    }
    ofs << "Address: " << address << std::endl;
    ofs << "Cost per kilogram: " << costPerKilogram << std::endl;
    ofs << "Count: " << size << std::endl;
    ofs << "Capacity: " << capacity << std::endl;
    ofs << "All weight: " << allWeight << std::endl;

    for (int i = 0; i < size; ++i) {
        list[i]->serialize(ofs);
    }
    ofs.close();
}

Item* Item::clone() {
    return new Item(*this);
}

