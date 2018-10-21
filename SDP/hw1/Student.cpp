//
// Created by yasen on 10/20/18.
//

#include <cstring>
#include <iostream>
#include "Student.h"

Student::Student() : name(nullptr), uni(nullptr) {}

Student::Student(const char* newName, const char* newUni) {
    name = new char[strlen(newName) + 1];
    strcpy(name, newName);
    uni = new char[strlen(newUni) + 1];
    strcpy(uni, newUni);
}

Student& Student::operator=(const Student& other) {
    if(this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

Student::~Student() {
    clear();
}

std::ostream &operator<<(std::ostream &os, const Student &obj) {
    os << '(' << obj.name << ", " << obj.uni << ')';
    return os;
}

void Student::clear() {
    delete[] name;
    delete[] uni;
}

void Student::copy(const Student& other) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    uni = new char[strlen(other.uni) + 1];
    strcpy(uni, other.uni);
}

bool operator==(const Student& s1, const Student& s2) {
    return strcmp(s1.name, s2.name) == 0;
}

