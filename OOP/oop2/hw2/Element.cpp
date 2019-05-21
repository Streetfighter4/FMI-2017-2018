//
// Created by yasen on 4/20/19.
//

#include "Element.h"

Element::Element(const char* materialName, size_t newWeight, bool isBreakable) :
        material(materialName, isBreakable), weight(newWeight) {}

void Element::print() const {
    material.print();
    std::cout << "Weight is: " << weight << std::endl;
}

void Element::serialize(std::ofstream& ofs) {
    material.serialize(ofs);
    ofs << "Element weight: " << weight << std::endl;
}

