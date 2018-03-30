//
// Created by yasen on 3/28/18.
//

#include <string.h>
#include <iostream>
#include "Tank.h"
using std::cout;
using std::endl;

Tank::Tank() : name(nullptr), shotPower(0.0), lifePoints(0.0){}

Tank::Tank(const char* name, double shotPower, double lifePoints) : shotPower(shotPower), lifePoints(lifePoints){
    name = new char[strlen(name)];
}

Tank::~Tank() {
    delete[] name;
}

void Tank::serialize(ofstream& outFile) {

    std::cout << "3" << std::endl;
    if(!outFile.is_open()) {
        std::cout << "File is not open" << std::endl;
        return;
    }

    std::cout << "4" << std::endl;
    size_t len = strlen(this->name);
    std::cout << "Len: " << len << endl;
    std::cout << "5" << std::endl;
    outFile.write((char*)&len, sizeof(len));

    std::cout << "6" << std::endl;
    if(!outFile) return;

    outFile.write(this->name, len);
    if(!outFile) return;

    std::cout << "7" << std::endl;
    //outFile.write((char*)&this->shotPower, len + sizeof(double));
    //if(!outFile) return;

    //outFile.write((char*)&this->lifePoints, len + (2*sizeof(double)));


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
