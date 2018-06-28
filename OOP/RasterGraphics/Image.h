//
// Created by yasen on 6/26/18.
//

#ifndef RASTERGRAPHICS_IMAGE_H
#define RASTERGRAPHICS_IMAGE_H

#include "Command.h"
#include "CommandConteiner.h"

class Image {
protected:
    char* filename;
    size_t width;
    size_t height;
    int** data;
private:
    void copy(const Image&);
public:

    CommandConteiner<COMMAND>* commands;
public:

    Image(char* filename);
    Image&operator=(const Image&);
    ~Image();
};


#endif //RASTERGRAPHICS_IMAGE_H
