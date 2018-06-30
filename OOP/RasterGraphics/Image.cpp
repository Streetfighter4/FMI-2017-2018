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
        std::cout << commands[i] << std::endl;
    }
}

char* Image::getCurrentDate() {
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    std::string data;
    data = std::to_string(now->tm_year+1900) + '-' +
              std::to_string(now->tm_mon + 1) + '-' +
              std::to_string(now->tm_mday) + '-' +
              std::to_string(now->tm_hour) + '-' +
              std::to_string(now->tm_min) + '-' +
                std::to_string(now->tm_sec);
    char* buff = new char[data.length() + 1];
    std::strcpy(buff, data.c_str());
    return buff;
}

char* Image::fileNameWithoutExtention(char *filename) {
    if (filename == nullptr)
        return nullptr;

    size_t lenght = strlen(filename);
    size_t i;
    for (i = lenght; i > 0 ; --i) {
        if(filename[i] == '.') break;
    }
    //image01.ppm
    //012345678910
    char* newFileName = new char[i];
    strncpy(newFileName, filename, i);

    return newFileName;
}

