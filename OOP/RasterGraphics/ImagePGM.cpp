//
// Created by yasen on 6/28/18.
//

#include <cstring>
#include <fstream>
#include <iostream>
#include "ImagePGM.h"

ImagePGM::ImagePGM(char *filename) : Image(filename) {
    std::ifstream ifs(filename);
    char line[1024];
    ifs.getline(line, 1024);
    if(strcmp(line, "P2") != 0) {
        std::cerr << "Version error" << std::endl;
    }
    ifs.getline(line, 1024);
    width = static_cast<size_t>(ifs.get());
    height = static_cast<size_t>(ifs.get());
    maxValueOfWhite = static_cast<size_t>(ifs.get());

    data = new int*[width];
    for (int i = 0; i < width; ++i) {
        data[i] = new int[height];
    }

    for (int j = 0; j < width; ++j) {
        for (int k = 0; k < height; ++k) {
            //TODO: check if value of each pixel is lower then max value of white
            data[j][k] = ifs.get();
        }
    }

    ifs.close();

}
