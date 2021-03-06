//
// Created by yasen on 6/28/18.
//

#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "ImagePGM.h"
#include "Helper.h"

ImagePGM::ImagePGM(char *filename) : Image(filename) {
    try{
        parse(filename);
    } catch(std::exception e) {
        std::cerr << e.what() << std::endl;
    }
}

ImagePGM::ImagePGM(const ImagePGM& other) : Image(other), isMonoChrome(other.isMonoChrome) {
    data = new size_t[height*width];
    for (int j = 0; j < height; ++j) {
        data[j] = other.data[j];
    }
}

void ImagePGM::parse(char* filename) {
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
    data = new size_t[height*width];
    bool isMonoPixel = false;
    size_t pixel;
    for (int j = 0; j < height*width; ++j) {
        ifs >> pixel;
        if (pixel > maxValueOfWhite || pixel < 0) {
            free();
            throw std::invalid_argument("Invalid value of pixel");
        }
        isMonoPixel = (pixel == 0 || pixel == maxValueOfWhite);
        if(!isMonoPixel) isMonoChrome = false;
        data[j] = pixel;
    }

    ifs.close();

}

void ImagePGM::save() {
    size_t countRightRotation = 0;
    size_t countLeftRotation = 0;
    while(!commands.isEmpty()) {
        COMMAND command = commands.pop_front();
        if(command == 2 && !isMonoChrome) {
            monoChrome();
            isMonoChrome = true;
        }
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

void ImagePGM::monoChrome() {
    for (int i = 0; i < height*width; ++i) {
        data[i] = ((data[i] > maxValueOfWhite/2) ? maxValueOfWhite : 0);
    }

}

void ImagePGM::negative() {
    for (int i = 0; i < height*width; ++i) {
        data[i] = maxValueOfWhite - data[i];
    }
}

void ImagePGM::writeInFile(char* filename) {
    char* fileNameWithoutExt = Helper::fileNameWithoutExtension(filename);
    char* date = Helper::getCurrentDate();
    char* newFileName = new char[strlen(filename) + strlen(date) + 2];
    strcpy(newFileName, fileNameWithoutExt);
    strcat(newFileName, "_");
    strcat(newFileName, date);
    strcat(newFileName, ".pgm");

    std::ofstream ofs(newFileName);
    ofs << "P2\n";
    ofs << width << " " << height << "\n";
    ofs << maxValueOfWhite << "\n";
    for (int i = 0; i < width*height; ++i) {
        ofs << data[i] << " ";
    }

    delete[] newFileName;
    delete[] fileNameWithoutExt;
    delete[] date;
    ofs.close();
}
