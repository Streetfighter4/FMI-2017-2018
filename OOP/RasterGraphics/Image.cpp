//
// Created by yasen on 6/26/18.
//

#include <cstring>
#include <iostream>
#include "Image.h"

Image::Image(char* filename) : commands(nullptr), width(0), height(0), data(nullptr) {
    this->filename = new char[strlen(filename) + 1];
    strcpy(this->filename, filename);
}

Image::~Image() {
    delete[] filename;
    delete commands;
}

Image& Image::operator=(const Image& other) {
    if(this != &other) {
        copy(other);
    }
    return *this;
}

void Image::copy(const Image& other) {
    width = other.width;
    height = other.height;

    this->filename = new char[strlen(other.filename) + 1];
    strcpy(this->filename, other.filename);
}
