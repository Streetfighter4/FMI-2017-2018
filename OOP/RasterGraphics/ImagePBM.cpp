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
    data = new int*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new int[width];
    }
    for (int j = 0; j < height; ++j) {
        for (int k = 0; k < width; ++k) {
            data[j][k] = other.data[j][k];
        }
    }
}

ImagePBM::~ImagePBM() {
    free();
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

    data = new int*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new int[width];
    }

    for (int j = 0; j < height; ++j) {
        for (int k = 0; k < width; ++k) {
            ifs >> word;
            int pixel = atoi(word);
            if(pixel == 0 || pixel == 1) {
                data[j][k] = pixel;
            } else {
                free();
            }
        }
    }

    ifs.close();

}

Image* ImagePBM::clone() {
    return new ImagePBM(*this);
}

void ImagePBM::negative() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            data[i][j] = 1 - data[i][j];
        }
    }
}

void ImagePBM::save() {
    size_t countRightRotation = 0;
    size_t countLeftRotation = 0;
    while(!commands.isEmpty()) {
        COMMAND command = commands.pop_front();
        if(command == 3) {
            negative();
        }
        if(command == 4) {
            countLeftRotation++;
        }
        if(command == 5) {
            countRightRotation++;
        }
    }

    int countRotation = countRightRotation%4 - countLeftRotation%4;
    makeRotations(countRotation);

    try {
        writeInFile(filename);
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
}

void ImagePBM::free() {
    delete[] filename;
    for (int i = 0; i < height; ++i) {
        delete data[i];
    }
    delete[] data;
    data = nullptr;
    width = 0;
    height = 0;
}

void ImagePBM::writeInFile(char *filename) {
    char* fileNameWithoutExt = fileNameWithoutExtension(filename);
    char* date = getCurrentDate();
    char* newFileName = new char[strlen(filename) + strlen(date) + 2];
    strcpy(newFileName, fileNameWithoutExt);
    strcat(newFileName, "_");
    strcat(newFileName, date);
    strcat(newFileName, ".pbm");

    std::ofstream ofs(newFileName);
    ofs << "P1\n";
    ofs << width << " " << height << "\n";
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            ofs << data[i][j] << " ";
        }
        ofs << "\n";
    }

    delete[] newFileName;
    delete[] fileNameWithoutExt;
    delete[] date;
    ofs.close();
}



