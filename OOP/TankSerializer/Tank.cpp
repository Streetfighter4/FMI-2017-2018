//
// Created by yasen on 3/28/18.
//

#include <string.h>
#include <iostream>
#include "Tank.h"
using std::cout;
using std::endl;

Tank::Tank() : name(nullptr), shotPower(0.0), lifePoints(0.0){}

Tank::Tank(const char* newName, double shotPower, double lifePoints) : shotPower(shotPower), lifePoints(lifePoints){
    size_t size = strlen(newName) + 1;
    name = new char[size];
    strcpy(name, newName);
    name[size] = '\0';
}

Tank::~Tank() {
    delete[] name;
}

void Tank::serialize(ofstream& outFile) {
    if(!outFile.is_open()) {
        std::cout << "File is not open" << std::endl;
        return;
    }

    size_t len = strlen(this->name);
    outFile.write((const char*)&len, sizeof(size_t));

    outFile.write(this->name, len);

    outFile.write((const char*)&this->shotPower, sizeof(double));

    outFile.write((const char*)&this->lifePoints, sizeof(double));

    if (outFile.good())
        std::cout << "Successfully serialize" << std::endl;
    else
        std::cout << "Serialize failed" << std::endl;

}

void Tank::deserialize(ifstream& inFile) {
    if(!inFile.is_open()) {
        std::cout << "File is not open" << std::endl;
        return;
    }
    size_t size;
    inFile.read((char*)&size, sizeof(size_t));
    if(!inFile)
        return;

    delete[] this->name;
    this->name = new char[size+1];

    size_t readBytes = 0;

    while (readBytes < size) {
        inFile.read(this->name + readBytes, size - readBytes);
        if(!inFile) return;
        readBytes += inFile.gcount();
    }

    this->name[size] = '\0';

    inFile.read((char*)&this->shotPower, sizeof(double));
    inFile.read((char*)&this->lifePoints, sizeof(double));

    if (inFile.good())
        std::cout << "Successfully deserialize" << std::endl;
    else
        std::cout << "Deserialize failed" << std::endl;
}

void Tank::tankInfo() const {
    cout << "Name: " << this->name << endl
         << "ShotPower: " << this->shotPower << endl
         << "LifePoint: " << this->lifePoints << endl;
}

char* Tank::getName() const { return name; }
double Tank::getShotPower() const { return shotPower; }
double Tank::getLifePoints() const { return lifePoints; }

void Tank::setName(char* newName) {
    size_t size = strlen(newName) + 1;
    name = new char[size];
    strcpy(name, newName);
    name[size] = '\0';
}
void Tank::setShotPower(double shotPower) {
    this->shotPower = shotPower;
}
void Tank::setLifePoints(double lifePoints) {
    this->lifePoints = lifePoints;
}


