//
// Created by yasen on 4/20/19.
//

#include "Material.h"

void Material::clean() {
    delete[] name;
    name = nullptr;
}

void Material::copy(const Material& other) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    isBreakable = other.isBreakable;
}

Material::Material(const char* newName, bool newIsBreakable) : isBreakable(newIsBreakable) {
    name = new char[strlen(newName) + 1];
    strcpy(name, newName);
}

Material::Material(const Material& other) {
    copy(other);
}

Material& Material::operator=(const Material& rhs) {
    if(this != &rhs) {
        clean();
        copy(rhs);
    }
    return *this;
}

Material::~Material() {
    clean();
}

void Material::print() const {
    std::cout << "Material '"<< name << "' is " << (isBreakable ? "breakable!\n" : "not breakable!\n");
}

void Material::serialize(std::ofstream& ofs) {
    ofs << name << " ";
    ofs << (isBreakable ? "is breakable\n" : "is't breakable\n");
}
