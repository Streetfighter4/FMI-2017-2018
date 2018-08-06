//
// Created by yasen on 6/26/18.
//

#include <cstring>
#include <iostream>
#include <ctime>
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
    free();
}

void Image::listCommands() {
    for (int i = 0; i < commands.getSize(); ++i) {
        if(commands[i] == 1)
            std::cout << "grayscale, ";
        if(commands[i] == 2)
            std::cout << "monochrome, ";
        if(commands[i] == 3)
            std::cout << "negative, ";
        if(commands[i] == 4)
            std::cout << "rotate left, ";
        if(commands[i] == 5)
            std::cout << "rotate right, ";

    }
    std::cout << std::endl;
}


void Image::rotateLeft() {
    size_t* temp = new size_t[height*width];
    //TODO: TEST THIS
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            temp[i*height+j] = data[(width*(j+1))-(i+1)];
        }
    }

    delete[] data;
    std::swap(height, width);
    data = temp;
}

void Image::rotateRight() {
    size_t* temp = new size_t[height*width];
    //TODO: TEST THIS
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            temp[(height-i-1)*(j+1)+((i+1)*j)] = data[i*width+j];
        }
    }

    delete[] data;
    std::swap(height, width);
    data = temp;
}

void Image::makeRotations(int countRotation) {
    for (int k = 0; k < abs(countRotation); ++k) {
        if(countRotation < 0) {
            rotateLeft();
        } else {
            rotateRight();
        }
    }
}

void Image::free() {
    delete[] filename;
    delete[] data;
    data = nullptr;
    width = 0;
    height = 0;
}
