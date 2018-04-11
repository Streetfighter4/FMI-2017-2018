//
// Created by yasen on 4/4/18.
//

#ifndef TANKSERIALIZER_ARMY_H
#define TANKSERIALIZER_ARMY_H


#include "Tank.h"

class Army {
    Tank* tanks;
    size_t currSize;
    size_t capacity;
public:
    Army();
    Army(size_t);
    Army(const Army&);
    ~Army();
    void resize(size_t);
    void addTank(const Tank&);

    size_t getCurrSize() const;
    size_t getCapacity() const;


    void serializeArmy(ofstream&);
    void deserializeArmy(ifstream&);

    void sortingTanks();

    void remove(Tank& tank);
    void attack(Tank&);
};


#endif //TANKSERIALIZER_ARMY_H
