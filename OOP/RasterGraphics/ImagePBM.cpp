//
// Created by yasen on 6/28/18.
//

#include <fstream>
#include <cstring>
#include <iostream>
#include "ImagePBM.h"

ImagePBM::ImagePBM(char* filename) : Image(filename) {
    try{
        parse(filename);
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }
}


ImagePBM::ImagePBM(const ImagePBM& other) : Image(other) {
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

void ImagePBM::parse(char *filename) {
std::ifstream ifs(filename);
    char word[1024] = { 0 };
    char line[1024];

    ifs >> word;
    while(!strcmp(word, "#")){
        ifs.getline(line, 1024);
        ifs >> word;
    }
    if(strcmp(word, "P1") != 0) {
        std::cerr << "Version error" << std::endl;
    }
    ifs >> word;
    while(!strcmp(word, "#")){
        ifs.getline(line, 1024);
        ifs >> word;
    }
    width = static_cast<size_t>(atoi(word));
    ifs >> word;
    height = static_cast<size_t>(atoi(word));
    ifs >> word;
    while(!strcmp(word, "#")){
        ifs.getline(line, 1024);
        ifs >> word;
    }

    data = new int*[width];
    for (int i = 0; i < width; ++i) {
        data[i] = new int[height];
    }

    for (int j = 0; j < width; ++j) {
        for (int k = 0; k < height; ++k) {
            ifs >> word;
            data[j][k] = atoi(word);
        }
    }

    ifs.close();

}

Image* ImagePBM::clone() {
    return new ImagePBM(*this);
}

void ImagePBM::save() {
    while(!commands.isEmpty()) {
        COMMAND command = commands.pop_front();
        if(command == 3) {
            negative();
        }
    }

}

void ImagePBM::negative() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            data[i][j] ^= 1;
        }
    }
}



