//
// Created by yasen on 7/30/18.
//

#ifndef RASTERGRAPHICS_HELPER_H
#define RASTERGRAPHICS_HELPER_H

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>

namespace Helper {
    inline char* fileNameWithoutExtension(char* filename) {
        if (filename == nullptr)
            return nullptr;

        size_t length = strlen(filename);
        size_t i;
        for (i = length; i > 0 ; --i) {
            if(filename[i] == '.') break;
        }

        char* newFileName = new char[i+1];
        strncpy(newFileName, filename, i);
        newFileName[i] = '\0';
        return newFileName;
    }

    inline char* getCurrentDate() {
        std::time_t t = std::time(0);   // get time now
        std::tm* now = std::localtime(&t);
        std::string data;
        data.append(std::to_string(now->tm_year+1900));
        data.append(".");
        data.append(std::to_string(now->tm_mon + 1));
        data.append(".");
        data.append(std::to_string(now->tm_mday));
        data.append("-");
        data.append(std::to_string(now->tm_hour));
        data.append(":");
        data.append(std::to_string(now->tm_min));
        data.append(":");
        data.append(std::to_string(now->tm_sec));

        char* buff = new char[data.length() + 1];
        std::strcpy(buff, data.c_str());
        return buff;
    }

    inline void getPixelsFromNumber(size_t& pixel1, size_t& pixel2, size_t& pixel3, size_t number) {
        int mask1 = 0, mask2 = 0, mask3 = 0;
        for (int j = 0; j < 8; ++j) {
            mask3 ^= (1 << j);
            mask2 ^= (1 << (j + 8));
            mask1 ^= (1 << (j + 16));
        }
        pixel1 = number & mask1;
        pixel1 >>= 16;
        pixel2 = number & mask2;
        pixel2 >>= 8;
        pixel3 = number & mask3;
    }

}
#endif //RASTERGRAPHICS_HELPER_H
