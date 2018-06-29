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
    //TODO: free alocated data
    maxValueOfPixel = other.maxValueOfPixel;
    isGrayScale = other.isGrayScale;
    data = new int*[width*3];
    for (int i = 0; i < width*3; ++i) {
        data[i] = new int[height];
    }
    for (int j = 0; j < width*3; ++j) {
        for (int k = 0; k < height; ++k) {
            data[j][k] = other.data[j][k];
        }
    }
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
    data = new int*[width*3];
    for (int i = 0; i < width*3; ++i) {
        data[i] = new int[height];
    }

    for (int j = 0; j < width*3; ++j) {
        for (int k = 0; k < height; ++k) {
            ifs >> word;
            if (atoi(word) > maxValueOfPixel) {
                //TODO: free allocated memory
                throw std::invalid_argument("Invalid value of pixel");
            }
            data[j][k] = atoi(word);
        }
    }
    isGrayScale = false; //TODO: for now
    ifs.close();

}

Image *ImagePPM::clone() {
    return new ImagePPM(*this);
}

void ImagePPM::save() {
    while(!commands.isEmpty()) {
        COMMAND command = commands.pop_front();
        if(command == 1 && !isGrayScale) {
            grayScale();
            isGrayScale = true;
        }
        if(command == 2) {
            monoChrome();
        }
        if(command == 3) {
            negative();
        }
    }

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

