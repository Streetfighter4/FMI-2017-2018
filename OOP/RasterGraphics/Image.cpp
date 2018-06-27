//
// Created by yasen on 6/26/18.
//

#include <string.h>
#include "Image.h"

Image::Image(size_t id, char* filename) : id(id), commands(nullptr), width(0), height(0) {
    this->filename = new char[strlen(filename) + 1];
    strcpy(this->filename, filename);
}

Image::~Image() {
    delete commands;
}

Image& Image::operator=(const Image& other) {
    if(this != &other) {
        copy(other);
    }
    return *this;
}

void Image::copy(const Image& other) {
    id = other.id;
    width = other.width;
    height = other.height;

    this->filename = new char[strlen(other.filename) + 1];
    strcpy(this->filename, other.filename);
}
