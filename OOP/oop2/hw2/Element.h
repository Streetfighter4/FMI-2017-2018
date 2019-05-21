//
// Created by yasen on 4/20/19.
//

#ifndef HW2_ELEMENT_H
#define HW2_ELEMENT_H


#include <fstream>
#include "Material.h"

class Element {
    Material material;
    size_t weight;
public:
    Element(const char* materialName, size_t newWeight, bool isBreakable = false);
public:
    inline bool isBreakable() const { return material.is_breakable(); }
    inline size_t getWeight() const { return weight; }
    void print() const;
    void serialize(std::ofstream& ofs);
};


#endif //HW2_ELEMENT_H
