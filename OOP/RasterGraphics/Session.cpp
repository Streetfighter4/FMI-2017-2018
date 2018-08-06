//
// Created by yasen on 6/26/18.
//

#include <iostream>
#include <cstring>
#include "Session.h"
#include "ImagePGM.h"
#include "ImagePBM.h"
#include "ImagePPM.h"

Session::Session(size_t id, char* files, size_t countImages) : id(id), images(countImages) {
    char* token;
    token = strtok (files," ");

    while (token != nullptr) {
        images.push_back(createImage(token));
        token = strtok (nullptr, " ");
    }

}

Session& Session::operator=(const Session& other) {
    if(this != &other) {
        copy(other);
    }
    return *this;
}

void Session::grayScale() {
    for (int i = 0; i < images.getSize(); ++i) {
        images[i]->commands.push_back(GRAYSCALE);
    }
}

void Session::monoChrome() {
    for (int i = 0; i < images.getSize(); ++i) {
        images[i]->commands.push_back(MONOCHROME);
    }
}

void Session::negative() {
    for (int i = 0; i < images.getSize(); ++i) {
        images[i]->commands.push_back(NEGATIVE);
    }
}

void Session::rotateLeft() {
    for (int i = 0; i < images.getSize(); ++i) {
        images[i]->commands.push_back(ROTATELEFT);
    }
}

void Session::rotateRight() {
    for (int i = 0; i < images.getSize(); ++i) {
        images[i]->commands.push_back(ROTATERIGHT);
    }
}

void Session::undo() {
    for (int i = 0; i < images.getSize(); ++i) {
        images[i]->commands.pop_back();
    }
}

void Session::add(char *filename) {
    Image* image = createImage(filename);
    images.push_back(image);
}

void Session::copy(const Session& other) {
    id = other.id;
    images = other.images;
}

char* Session::getExtension(char* file) {
    size_t lenght = strlen(file);
    size_t i;
    for (i = lenght; i > 0 ; --i) {
        if(file[i] == '.') break;
    }
    char* extention = new char[lenght - i + 1];
    strcpy(extention, file+i+1);
    return extention;
}

Image* Session::createImage(char* file) {
    if (file == nullptr)
        return nullptr;

    char* extension = getExtension(file);
    if (strcmp(extension, "ppm") == 0) {
        delete[] extension;
        return new ImagePPM(file);
    }
    if (strcmp(extension, "pgm") == 0) {
        delete[] extension;
        return new ImagePGM(file);
    }
    if (strcmp(extension, "pbm") == 0) {
        delete[] extension;
        return new ImagePBM(file);
    }

    return nullptr;
}

void Session::listImages() const {
    std::cout << "List images: " << std::endl;
    for (int i = 0; i < images.getSize(); ++i) {
        std::cout << images[i]->getName() << std::endl;
        images[i]->listCommands();
    }
}

void Session::save() {
    for (int i = 0; i < images.getSize(); ++i) {
        images[i]->save();
    }
}


