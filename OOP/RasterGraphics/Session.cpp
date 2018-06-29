//
// Created by yasen on 6/26/18.
//

#include <iostream>
#include <cstring>
#include "Session.h"
#include "ImagePGM.h"
#include "ImagePBM.h"
#include "ImagePPM.h"

Session::Session(size_t id, char* files, size_t countImages) : id(id), countImages(countImages) {

    images = new Image*[countImages];
    int j = 0;
    char* token;
    token = strtok (files," ");

    while (token != NULL) {
        images[j++] = createImage(token);
        token = strtok (NULL, " ");
    }

}

Session::~Session() {
    for (int i = 0; i < countImages; ++i) {
        delete images[i];
    }
    delete[] images;
}

Session& Session::operator=(const Session& other) {
    if(this != &other) {
        copy(other);
    }
    return *this;
}

void Session::grayScale() {
    for (int i = 0; i < countImages; ++i) {
        images[i]->commands.push_back(GRAYSCALE);
    }
}

void Session::monoChrome() {
    for (int i = 0; i < countImages; ++i) {
        images[i]->commands.push_back(MONOCHROME);
    }
}

void Session::negative() {
    for (int i = 0; i < countImages; ++i) {
        images[i]->commands.push_back(NEGATIVE);
    }
}

void Session::rotateLeft() {
    for (int i = 0; i < countImages; ++i) {
        images[i]->commands.push_back(ROTATELEFT);
    }
}

void Session::rotateRight() {
    for (int i = 0; i < countImages; ++i) {
        images[i]->commands.push_back(ROTATERIGHT);
    }
}

void Session::undo() {
    for (int i = 0; i < countImages; ++i) {
        images[i]->commands.pop_back();
    }
}

void Session::add(char *filename) {
    Image* image = createImage(filename);
    Image** newImages = new Image*[countImages+1];

    for (size_t i = 0; i < countImages; i++) {
        newImages[i] = images[i]->clone();
    }
    newImages[countImages] = image;

    ++countImages;
    delete[] images;
    images = newImages;

}
void Session::copy(const Session& other) {
    id = other.id;
    delete[] images;
    images = new Image*[other.countImages];
    for (int i = 0; i < other.countImages; ++i) {
        images[i] = other.images[i];
    }
    countImages = other.countImages;
}

Image* Session::createImage(char* file) {
    if (file == nullptr)
        return nullptr;

    size_t lenght = strlen(file);
    size_t i;
    for (i = lenght; i > 0 ; --i) {
        if(file[i] == '.') break;
    }
    char* extention = new char[lenght - i + 1];
    strcpy(extention, file+i+1);
    if (strcmp(extention, "ppm") == 0) {
        return new ImagePPM(file);
    }
    if (strcmp(extention, "pgm") == 0) {
        return new ImagePGM(file);
    }
    if (strcmp(extention, "pbm") == 0) {
        return new ImagePBM(file);
    }

    return nullptr;
}

void Session::listImages() {
    std::cout << "List images: " << std::endl;
    for (int i = 0; i < countImages; ++i) {
        std::cout << images[i]->getName() << std::endl;
        images[i]->listCommands();
    }
}

void Session::save() {
    for (int i = 0; i < countImages; ++i) {
        images[i]->save();
    }
}
