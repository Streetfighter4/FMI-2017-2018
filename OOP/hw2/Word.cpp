//
// Created by yasen on 4/3/18.
//
#include <iostream>
#include <string.h>
#include "Word.h"

using std::cout;
using std::endl;

Word::Word() {}

Word::Word(size_t id, char *value) : id(id){
    this->value = new char[strlen(value)];
    strcpy(this->value, value);
}

Word::~Word() {
    delete[] value;
}

size_t Word::getId() const {
    return id;
}

char* Word::getValue() const {
    return value;
}

Word& Word::operator=(const Word& other) {
    this->id = other.id;
    value = new char[strlen(other.value) + 1];
    strcpy(value, other.value);

    return *this;
}

bool Word::getIsBold() const {
    return isBold;
}

bool Word::getIsItalic() const {
    return isItalic;
}

void Word::setIsBold(bool isBold) {
    this->isBold = isBold;
}

void Word::setIsItalic(bool isItalic) {
    this->isItalic = isItalic;
}

