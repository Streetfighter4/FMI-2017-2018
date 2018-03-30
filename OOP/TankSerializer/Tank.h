//
// Created by yasen on 3/28/18.
//

#ifndef TANKSERIALIZER_TANK_H
#define TANKSERIALIZER_TANK_H

#include <fstream>
using std::ofstream;
using std::ifstream;

class Tank {
    char* name;
    double shotPower;
    double lifePoints;

public:
    Tank();
    Tank(const char* name, double shotPower, double lifePoints);
    ~Tank();

    void serialize(ofstream& outFile);
    void deserialize(ifstream& inFile);
    void tankInfo() const;
    char* getName() const;
    double getShotPower() const;
    double getLifePoints() const;

    void setName(char* name);
    void setShotPower(double shotPower);
    void setLifePoints(double LifePoints);
};


#endif //TANKSERIALIZER_TANK_H
