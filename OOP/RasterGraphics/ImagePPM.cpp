//
// Created by yasen on 6/28/18.
//

#include <fstream>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include "ImagePPM.h"
#include "Helper.h"

ImagePPM::ImagePPM(char* filename) : Image(filename) {
    try {
        parse(filename);
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }

}

ImagePPM::ImagePPM(const ImagePPM& other) : Image(other),
                                            maxValueOfPixel(other.maxValueOfPixel),
                                            isGrayScale(other.isGrayScale),
                                            isMonoChrome(other.isMonoChrome) {

    data = new size_t[height*width];
    for (int j = 0; j < other.height*width; ++j) {
        data[j] = other.data[j];
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
    data = new size_t[height*width];
    for (int i = 0; i < height*width; ++i) {
        data[i] = 0;
    }
    bool isGrayPixel = false;
    bool isMonoPixel = false;
    size_t pixel1, pixel2, pixel3;
    for (int j = 0; j < height*width; ++j) {
        ifs >> pixel1 >> pixel2 >> pixel3;
        if (pixel1 > maxValueOfPixel || pixel2 > maxValueOfPixel || pixel3 > maxValueOfPixel) {
            free();
            throw std::invalid_argument("Invalid value of pixel");
        }
        isGrayPixel = isEqual(pixel1, pixel2, pixel3);
        if(!isGrayPixel) isGrayScale = false;
        isMonoPixel = isBlackOrWhite(pixel1, pixel2, pixel3);
        if(!isMonoPixel) isMonoChrome = false;
        ((data[j] ^= pixel1<<16) ^= pixel2<<8) ^= pixel3;
    }

    ifs.close();

}

void ImagePPM::save() {
    size_t countRightRotation = 0;
    size_t countLeftRotation = 0;
    while(!commands.isEmpty()) {
        COMMAND command = commands.pop_front();
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
        if(command == 4) {
            countLeftRotation++;
        }
        if(command == 5) {
            countRightRotation++;
        }
    }

    int countRotation = static_cast<int>(countRightRotation % 4 - countLeftRotation % 4);
    makeRotations(countRotation);

    try {
        writeInFile(filename);
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
}

void ImagePPM::grayScale() {
    size_t pixel1, pixel2, pixel3;
    for (int i = 0; i < height*width; ++i) {
        Helper::getPixelsFromNumber(pixel1, pixel2, pixel3, data[i]);
        size_t average = ((pixel1 + pixel2 + pixel3)/3);
        data[i] = 0;
        ((data[i] ^= average<<16) ^= average<<8) ^= average;
    }
}

void ImagePPM::monoChrome() {
    size_t pixel1, pixel2, pixel3;

    for (int i = 0; i < height*width; ++i) {
        Helper::getPixelsFromNumber(pixel1, pixel2, pixel3, data[i]);

        if((pixel1+pixel2+pixel3/3) > maxValueOfPixel/2) {
            data[i] = 0;
            ((data[i] ^= maxValueOfPixel<<16) ^= maxValueOfPixel << 8) ^= maxValueOfPixel;
        } else {
            data[i] = 0;
        }
    }
}

void ImagePPM::negative() {
    size_t pixel1, pixel2, pixel3;

    for (int i = 0; i < height*width; ++i) {
        Helper::getPixelsFromNumber(pixel1, pixel2, pixel3, data[i]);
        data[i] = 0;
        data[i] ^= (maxValueOfPixel-pixel1)<<16;
        data[i] ^= (maxValueOfPixel-pixel2)<<8;
        data[i] ^= (maxValueOfPixel-pixel3);
    }
}

bool ImagePPM::isEqual(const size_t& a, const size_t& b, const size_t& c) const {
    return (a == b && b == c);
}

bool ImagePPM::isBlackOrWhite(const size_t& a, const size_t& b, const size_t& c) const {
    return (isEqual(a, b, c) && (a == 0 || a == maxValueOfPixel));
}

void ImagePPM::writeInFile(char *filename) const {
    char* fileNameWithoutExt = Helper::fileNameWithoutExtension(filename);
    char* date = Helper::getCurrentDate();
    char* newFileName = new char[strlen(filename) + strlen(date) + 2];
    strcpy(newFileName, fileNameWithoutExt);
    strcat(newFileName, "_");
    strcat(newFileName, date);
    strcat(newFileName, ".ppm");

    std::ofstream ofs(newFileName);
    ofs << "P3\n";
    ofs << width << " " << height << "\n";
    ofs << maxValueOfPixel << "\n";
    size_t pixel1, pixel2, pixel3;
    for (int i = 0; i < height*width; ++i) {
        pixel1 = pixel2 = pixel3 = 0;
        Helper::getPixelsFromNumber(pixel1, pixel2, pixel3, data[i]);
        ofs << pixel1 << " " << pixel2 << " " << pixel3 << " ";
    }

    delete[] newFileName;
    delete[] fileNameWithoutExt;
    delete[] date;
    ofs.close();

}

