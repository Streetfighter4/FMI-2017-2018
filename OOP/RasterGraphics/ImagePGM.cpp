//
// Created by yasen on 6/28/18.
//

#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "ImagePGM.h"

ImagePGM::ImagePGM(char *filename) : Image(filename) {
    try{
        parse(filename);
    } catch(std::exception e) {
        std::cerr << e.what() << std::endl;
    }
}

ImagePGM::ImagePGM(const ImagePGM& other) : Image(other) {
    //TODO: free alocated data
    data = new int*[width];
    for (int i = 0; i < width; ++i) {
        data[i] = new int[height];
    }
    for (int j = 0; j < width; ++j) {
        for (int k = 0; k < height; ++k) {
            data[j][k] = other.data[j][k];
        }
    }

}

void ImagePGM::parse(char *filename) {
    std::ifstream ifs(filename);
    char word[1024] = {0};
    char line[1024];

    ifs >> word;
    while (!strcmp(word, "#")) {
        ifs.getline(line, 1024);
        ifs >> word;
    }
    if (strcmp(word, "P2") != 0) {
        std::cerr << "Version error" << std::endl;
    }
    ifs >> word;
    while (!strcmp(word, "#")) {
        ifs.getline(line, 1024);
        ifs >> word;
    }
    width = static_cast<size_t>(atoi(word));
    ifs >> word;
    height = static_cast<size_t>(atoi(word));
    ifs >> word;
    while (!strcmp(word, "#")) {
        ifs.getline(line, 1024);
        ifs >> word;
    }
    maxValueOfWhite = static_cast<size_t>(atoi(word));
    data = new int *[width];
    for (int i = 0; i < width; ++i) {
        data[i] = new int[height];
    }
    for (int j = 0; j < width; ++j) {
        for (int k = 0; k < height; ++k) {
            ifs >> word;
            if (atoi(word) > maxValueOfWhite) {
                //TODO: free allocated memory
                throw std::invalid_argument("Invalid value of pixel");
            }
            data[j][k] = atoi(word);
        }
    }

    ifs.close();

}

Image* ImagePGM::clone() {
    return new ImagePGM(*this);
}

void ImagePGM::save() {
    while(!commands.isEmpty()) {
        COMMAND command = commands.pop_front();
        if(command == 2) {
            monoChrome();
        }
        if(command == 3) {
            negative();
        }
    }
}

void ImagePGM::monoChrome() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if(data[i][j] > maxValueOfWhite/2) {
                data[i][j] = maxValueOfWhite;
            } else {
                data[i][j] = 0;
            }
        }
    }

}

void ImagePGM::negative() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            data[i][j] = maxValueOfWhite - data[i][j];
        }
    }

}

