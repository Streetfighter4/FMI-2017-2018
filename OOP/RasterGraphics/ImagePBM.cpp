//
// Created by yasen on 6/28/18.
//

#include <fstream>
#include <cstring>
#include <iostream>
#include "ImagePBM.h"

ImagePBM::ImagePBM(char* filename) : Image(filename) {
    std::ifstream ifs(filename);
    char* word = nullptr;
    while (!ifs.eof()){
        ifs >> word;
        if(strcmp(word, "P1") != 0) {
            std::cerr << "Version error" << std::endl;
        }
        if(strcmp(word, "#") == 0) {
        }
        width = static_cast<size_t>(ifs.get());
        height = static_cast<size_t>(ifs.get());

        data = new int*[width];
        for (int i = 0; i < width; ++i) {
            data[i] = new int[height];
        }

        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < height; ++k) {
                data[j][k] = ifs.get();
            }
        }
    }

    ifs.close();
}
