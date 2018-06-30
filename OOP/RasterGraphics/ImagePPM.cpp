//
// Created by yasen on 6/28/18.
//

#include <fstream>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include "ImagePPM.h"

ImagePPM::ImagePPM(char* filename) : Image(filename) {
    try {
        parse(filename);
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }

}

ImagePPM::ImagePPM(const ImagePPM& other) : Image(other) {
    maxValueOfPixel = other.maxValueOfPixel;
    isGrayScale = other.isGrayScale;
    isMonoChrome = other.isMonoChrome;
    data = new int*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new int[width*3];
    }
    for (int j = 0; j < height; ++j) {
        for (int k = 0; k < width*3; ++k) {
            data[j][k] = other.data[j][k];
        }
    }
}

ImagePPM::~ImagePPM() {
    free();
}

void ImagePPM::parse(char *filename) {
    std::ifstream ifs(filename);
    char word[1024] = { 0 };
    char line[1024];

    ifs >> word;

    while (strcmp(word, "#") == 0) {
        ifs.getline(line, 1024);
        ifs >> word;
    }

    if (strcmp(word, "P3") != 0) {
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
    maxValueOfPixel = static_cast<size_t>(atoi(word));
    data = new int*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new int[width*3];
    }

    for (int j = 0; j < height; ++j) {
        for (int k = 0; k < width*3; ++k) {
            ifs >> word;
            if (atoi(word) > maxValueOfPixel) {
                free();
                throw std::invalid_argument("Invalid value of pixel");
            }
            if(k%3 == 2) {
                isGrayScale = isEqual(data[j][k-2], data[j][k-1], data[j][k]);
                isMonoChrome = isBlackOrWhite(data[j][k-2], data[j][k-1], data[j][k]);
            }
            data[j][k] = atoi(word);
        }
    }
    ifs.close();

}

Image *ImagePPM::clone() {
    return new ImagePPM(*this);
}

void ImagePPM::save() {
    for (int k = 0; k < commands.getSize(); ++k) {
        COMMAND command = commands[k];
        if(command == 1 && !isGrayScale) {
            grayScale();
            isGrayScale = true;
        }
        if(command == 2 && !isMonoChrome) {
            monoChrome();
            isMonoChrome = true;
        }
        if(command == 3) {
            negative();
        }
    }
    char* newFileName = new char[strlen(filename) + strlen(getCurrentDate()) + 2];
    strcpy(newFileName, fileNameWithoutExtention(filename));
    strcat(newFileName, "_");
    strcat(newFileName, getCurrentDate());
    strcat(newFileName, ".ppm");
    std::ofstream ofs(newFileName);
    ofs << "P3\n";
    ofs << width << " " << height << "\n";
    ofs << maxValueOfPixel << "\n";
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width*3; ++j) {
            ofs << data[i][j] << " ";
        }
        ofs << "\n";
    }

    ofs.close();

}

void ImagePPM::grayScale() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width*3; j+=3) {
            data[i][j] = data[i][j+1] = data[i][j+2] = ((data[i][j] + data[i][j+1] + data[i][j+2])/3);
        }
    }
}

void ImagePPM::monoChrome() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width*3; ++j) {
            if(((data[i][j] + data[i][j+1] + data[i][j+2])/3) > maxValueOfPixel/2) {
                data[i][j] = data[i][j+1] = data[i][j+2] = maxValueOfPixel;
            } else {
                data[i][j] = data[i][j+1] = data[i][j+2] = 0;
            }
        }
    }
}

void ImagePPM::negative() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width*3; ++j) {
            data[i][j] = maxValueOfPixel - data[i][j];
        }
    }
}

void ImagePPM::free() {
    delete[] filename;
    for (int i = 0; i < height; ++i) {
        delete data[i];
    }
    delete[] data;
    data = nullptr;
    width = 0;
    height = 0;
    maxValueOfPixel = 0;
    isGrayScale = false;
}

bool ImagePPM::isEqual(int a, int b, int c) {
    return (a == b && b == c);
}

bool ImagePPM::isBlackOrWhite(int a, int b, int c) {
    return (isEqual(a, b, c) && (a == 0 || a == maxValueOfPixel));
}

