//
// Created by yasen on 6/26/18.
//

#include "Session.h"

Session::Session(size_t id) : id(id), images(nullptr), countImages(0) {}

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
        images[i]->commands->push_back(GRAYSCALE);
    }
}

void Session::monoChrome() {
    for (int i = 0; i < countImages; ++i) {
        images[i]->commands->push_back(MONOCHROME);
    }
}

void Session::negative() {
    for (int i = 0; i < countImages; ++i) {
        images[i]->commands->push_back(NEGATIVE);
    }
}

void Session::rotateLeft() {
    for (int i = 0; i < countImages; ++i) {
        images[i]->commands->push_back(ROTATELEFT);
    }
}

void Session::rotateRight() {
    for (int i = 0; i < countImages; ++i) {
        images[i]->commands->push_back(ROTATERIGHT);
    }
}

void Session::undo() {
    for (int i = 0; i < countImages; ++i) {
        images[i]->commands->pop_back();
    }
}

void Session::add(size_t id, char *filename) {
    Image* image = new Image(id, filename);
    Image** temp = images;
    images = new Image*[countImages+1];

    for (size_t i = 0; i < countImages; i++) {
        images[i] = temp[i];
    }
    images[countImages] = image;

    for (int j = 0; j < countImages; ++j) {
        delete temp[j];
    }
    delete[] temp;

    countImages++;
}

void Session::copy(const Session& other) {
    id = other.id;
    delete[] images;
    delete images;
    images = new Image*[other.countImages];
    for (int i = 0; i < other.countImages; ++i) {
        images[i] = other.images[i];
    }
    countImages = other.countImages;
}
