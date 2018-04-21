//
// Created by yasen on 4/3/18.
//
#include <iostream>
#include <cstring>
#include "Word.h"

Word::Word():value(nullptr) {}

Word::Word(size_t id, char *value) : id(id), isBold(false), isItalic(false){
    this->value = new char[strlen(value) + 1];
    strcpy(this->value, value);
}

Word::~Word() {
    delete[] value;
}

const char* Word::getValue() const {
    return value;
}

Word& Word::operator=(const Word& other) {
    delete[] value;
    this->id = other.id;
    this->isBold = other.isBold;
    this->isItalic = other.isItalic;
    value = new (std::nothrow) char[strlen(other.value) + 1];
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

