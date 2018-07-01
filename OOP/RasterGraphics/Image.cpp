//
// Created by yasen on 6/26/18.
//

#include <cstring>
#include <iostream>
#include <ctime>
#include <cstdlib>
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

char* Image::getCurrentDate() {
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    std::string data;
    data = std::to_string(now->tm_year+1900) + '.' +
              std::to_string(now->tm_mon + 1) + '.' +
              std::to_string(now->tm_mday) + '-' +
              std::to_string(now->tm_hour) + ':' +
              std::to_string(now->tm_min) + ':' +
                std::to_string(now->tm_sec);
    char* buff = new char[data.length() + 1];
    std::strcpy(buff, data.c_str());
    return buff;
}

char* Image::fileNameWithoutExtension(char *filename) {
    if (filename == nullptr)
        return nullptr;

    size_t length = strlen(filename);
    size_t i;
    for (i = length; i > 0 ; --i) {
        if(filename[i] == '.') break;
    }
    //image01.ppm
    //012345678910
    char* newFileName = new char[i];
    strncpy(newFileName, filename, i);
    newFileName[i] = '\0';
    return newFileName;
}

void Image::rotateLeft() {
    int** temp = new int*[width];
    for (int i = 0; i < width; ++i) {
        temp[i] = new int[height];
    }

    for (int j = 0; j < height; ++j) {
        for (int k = 0; k < width; ++k) {
            temp[width-k-1][j] = data[j][k];
        }
    }

    for (int l = 0; l < height; ++l) {
        delete data[l];
    }
    delete[] data;
    size_t buff = width;
    width = height;
    height = buff;
    data = temp;
}

void Image::rotateRight() {
    int** temp = new int*[width];
    for (int i = 0; i < width; ++i) {
        temp[i] = new int[height];
    }

    for (int j = 0; j < height; ++j) {
        for (int k = 0; k < width; ++k) {
            temp[k][height-j-1] = data[j][k];
        }
    }

    for (int l = 0; l < height; ++l) {
        delete data[l];
    }
    delete[] data;
    size_t buff = width;
    width = height;
    height = buff;
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


