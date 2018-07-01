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
    bool isGrayPixel = false;
    bool isMonoPixel = false;
    for (int j = 0; j < height; ++j) {
        for (int k = 0; k < width*3; ++k) {
            ifs >> word;
            if (atoi(word) > maxValueOfPixel) {
                free();
                throw std::invalid_argument("Invalid value of pixel");
            }
            if(k%3 == 2) {
                isGrayPixel = isEqual(data[j][k-2], data[j][k-1], data[j][k]);
                if(!isGrayPixel) isGrayScale = false;
                isMonoPixel = isBlackOrWhite(data[j][k-2], data[j][k-1], data[j][k]);
                if(!isMonoPixel) isMonoChrome = false;
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

    int countRotation = countRightRotation%4 - countLeftRotation%4;
    makeRotations(countRotation);

    try {
        writeInFile(filename);
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
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
        for (int j = 0; j < width*3; j+=3) {
            if(((data[i][j] + data[i][j+1] + data[i][j+2])/3) > maxValueOfPixel/2) {
                data[i][j] = data[i][j+1] = data[i][j+2] = maxValueOfPixel;
            } else {
                data[i][j] = 0;
                data[i][j+1] = 0;
                data[i][j+2] = 0;
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

void ImagePPM::rotateLeft() {
    size_t newWidth = height*3;
    size_t newHeight = width;
    int** temp = new int*[newHeight];
    for (int i = 0; i < newHeight; ++i) {
        temp[i] = new int[newWidth];
    }

    for (int j = 0; j < height; ++j) {
        for (int k = 0, l = newHeight-1; l >= 0; k+=3, --l) {
            temp[l][j*3] = data[j][k];
        }

        for (int k = 1, l = newHeight-1; l >= 0; k+=3, --l) {
            temp[l][j*3+1] = data[j][k];
        }

        for (int k = 2, l = newHeight-1; l >= 0; k+=3, --l) {
            temp[l][j*3+2] = data[j][k];
        }
    }
    for (int l = 0; l < height; ++l) {
        delete data[l];
    }
    delete[] data;
    width = newWidth/3;
    height = newHeight;
    data = temp;
}

void ImagePPM::rotateRight() {
    size_t newWidth = height*3;
    size_t newHeight = width;
    int** temp = new int*[newHeight];
    for (int i = 0; i < newHeight; ++i) {
        temp[i] = new int[newWidth];
    }

    for (int j = 0; j < height; ++j) {
        for (int k = 0, l = 0; l < newHeight; k+=3, ++l) {
            temp[l][newWidth-1-(j*3+2)] = data[j][k];
        }

        for (int k = 1, l = 0; l < newHeight; k+=3, ++l) {
            temp[l][newWidth-1-(j*3+1)] = data[j][k];
        }

        for (int k = 2, l = 0; l < newHeight; k+=3, ++l) {
            temp[l][newWidth-1-j*3] = data[j][k];
        }
    }
    for (int l = 0; l < height; ++l) {
        delete data[l];
    }
    delete[] data;
    width = newWidth/3;
    height = newHeight;
    data = temp;

}

void ImagePPM::writeInFile(char *filename) {
    char* fileNameWithoutExt = fileNameWithoutExtension(filename);
    char* date = getCurrentDate();
    char* newFileName = new char[strlen(filename) + strlen(date) + 2];
    strcpy(newFileName, fileNameWithoutExt);
    strcat(newFileName, "_");
    strcat(newFileName, date);
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

    delete[] newFileName;
    delete[] fileNameWithoutExt;
    delete[] date;
    ofs.close();

}

