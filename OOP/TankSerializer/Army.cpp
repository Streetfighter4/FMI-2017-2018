//
// Created by yasen on 4/4/18.
//

#include <string.h>
#include <iostream>
#include "Army.h"
using std::cout;
using std::endl;

Army::Army() : tanks(nullptr), currSize(0), capacity(0) {}

Army::Army(size_t size) : currSize(0), capacity(size){
    tanks = new Tank[capacity];
}

Army::Army(const Army& otherArmy) : tanks(nullptr), currSize(0), capacity(0) {
    tanks = new Tank[otherArmy.capacity];
    for (int i = 0; i < otherArmy.currSize; ++i) {
        tanks[i] = otherArmy.tanks[i];
    }
    currSize = otherArmy.currSize;
    capacity = otherArmy.capacity;
}

Army::~Army() {
    delete[] tanks;
    tanks = nullptr;
    currSize = 0;
    capacity = 0;
}

void Army::resize(size_t newCap) {

    Tank* temp = tanks;

    //allocating new memory
    tanks = new Tank[newCap];

    for (size_t i = 0; i < currSize; i++)
        tanks[i] = temp[i];

    capacity = newCap;

    delete[] temp;
}

void Army::addTank(const Tank& tank) {
    if(currSize >= capacity) {
        size_t newCap = (capacity == 0) ? 2 : capacity * 2;
        resize(newCap);
    }
    tanks[currSize++] = tank;
}

void Army::serializeArmy(ofstream& file) {
    file.write((const char*)&currSize, sizeof(size_t));

    for (int i = 0; i < currSize; ++i) {
        tanks[i].serialize(file);
    }
    file.close();
}

void Army::deserializeArmy(ifstream& file) {
    size_t size;
    file.read((char*)&size, sizeof(size_t));

    for (int i = 0; i < size; ++i) {
        file.read((char*)&tanks[i], sizeof(Tank));
    }
}


void Army::sortingTanks() {
    for (int i = 0; i < currSize; ++i) {
        for (int j = i+1; j < currSize-1; ++j) {
            if(tanks[i].getShotPower() < tanks[j].getShotPower())
                std::swap(tanks[i], tanks[j]);
        }
    }
}

void Army::attack(Tank& tank) {
    sortingTanks();
    size_t countTanks = 0;
    double tankLifePoints = tank.getLifePoints();
    for (int i = 0; i < currSize; ++i) {
        if(tankLifePoints > 0.0) {
            tankLifePoints -= tanks[i].getShotPower();
            countTanks++;
        }
    }
    std::cout << "CountTanks: " << countTanks << std::endl;
    if (countTanks > 0) {
        for (int i = 0; i < countTanks; ++i) {
            tank.setLifePoints(tank.getLifePoints() - tanks[i].getShotPower());
        }
        if(tank.getLifePoints() <= 0.0) {
            std::cout << "Tank has been destroyed\nTank info:\n";
            tank.tankInfo();
            this->remove(tank);
        }
    } else {
        std::cout << "Not enough power on army" << std::endl;
        return;
    }

}

size_t Army::getCurrSize() const {
    return currSize;
}

size_t Army::getCapacity() const {
    return capacity;
}

void Army::remove(Tank& tank) {
    std::swap(tank, tanks[currSize]);
    currSize--;
}



