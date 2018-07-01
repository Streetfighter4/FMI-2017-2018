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

    while (token != nullptr) {
        images[j++] = createImage(token);
        token = strtok (nullptr, " ");
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

    delete[] extension;
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

Image* Session::checkImageExist(char* filename) {
    for (int i = 0; i < countImages; ++i) {
        if(strcmp(images[i]->getName(), filename) == 0) {
            return images[i];
        }
    }
    return nullptr;
}

void Session::makeHorizontalCollage(char* file1, char* file2) {
    Image* image1 = checkImageExist(file1);
    Image* image2 = checkImageExist(file2);

    if(image1 && image2) {
        char* fileName1 = image1->fileNameWithoutExtension(file1);
        char* fileName2 = image2->fileNameWithoutExtension(file1);

        char* extension1 = getExtension(file1);
        char* extension2 = getExtension(file2);
        if(strcmp(extension1, extension2) == 0) {
            char* newFileName = new char[strlen(fileName1) + strlen(fileName2) + strlen(extension1)+2];
            strcpy(newFileName, fileName1);
            strcat(newFileName, "_");
            strcat(newFileName, fileName2);
            strcat(newFileName, ".");
            strcat(newFileName, extension1);
            createImage(newFileName);
            delete[] fileName1;
            delete[] fileName2;
            delete[] newFileName;

        }
    }
}


