//
// Created by yasen on 3/28/18.
//

#include <string.h>
#include <iostream>
#include "Tank.h"
using std::cout;
using std::endl;

Tank::Tank() : name(nullptr), shotPower(0.0), lifePoints(0.0){}

Tank::Tank(char* name, double shotPower, double lifePoints) : shotPower(shotPower), lifePoints(lifePoints){
    name = new char[strlen(name)];
}

Tank::~Tank() {
    delete[] name;
}

void Tank::serialize(ofstream& outFile) {
    if(!outFile.is_open()) {
        std::cout << "File is not open" << std::endl;
        return;
    }

    outFile.write((const char*)this, sizeof(Tank));
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
    //if(inFile.flags() & std::ios::binary)
    inFile.read((char*)this, sizeof(Tank));
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
    name = new char[strlen(newName)];
    memcpy(name, newName, strlen(newName));
}
void Tank::setShotPower(double shotPower) {
    this->shotPower = shotPower;
}
void Tank::setLifePoints(double lifePoints) {
    this->lifePoints = lifePoints;
}
