//
// Created by yasen on 4/20/19.
//

#ifndef HW2_MATERIAL_H
#define HW2_MATERIAL_H

#include <iostream>
#include <cstring>
#include <fstream>

class Material {
    char* name;
    bool isBreakable;

private:
    void clean();
    void copy(const Material& other);
public:
    explicit Material(const char* newName, bool newIsBreakable = false);
    Material(const Material& other);
    Material&operator=(const Material& rhs);
    ~Material();
public:
    inline bool is_breakable() const { return isBreakable; }
    void print() const;
    void serialize(std::ofstream& ofs);
};


#endif //HW2_MATERIAL_H
