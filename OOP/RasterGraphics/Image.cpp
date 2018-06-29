//
// Created by yasen on 6/26/18.
//

#include <cstring>
#include <iostream>
#include "Image.h"

Image::Image(char* filename) : commands(2), width(0), height(0), data(nullptr) {
    this->filename = new char[strlen(filename) + 1];
    strcpy(this->filename, filename);
}

Image::Image(const Image& other) : Image(other.filename) {
    width = other.width;
    height = other.height;
    commands = other.commands;
}

Image::~Image() {
    delete[] filename;
}

void Image::listCommands() {
    for (int i = 0; i < commands.getSize(); ++i) {
        std::cout << commands[i] << std::endl;
    }
}

