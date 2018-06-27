//
// Created by yasen on 6/26/18.
//

#ifndef RASTERGRAPHICS_IMAGE_H
#define RASTERGRAPHICS_IMAGE_H

#include "Command.h"
#include "CommandConteiner.h"

class Image {
    size_t id;
    char* filename;
    size_t width;
    size_t height;

    void copy(const Image&);
public:

    CommandConteiner<COMMAND>* commands;
public:

    Image(size_t id, char* filename);
    Image&operator=(const Image&);
    ~Image();
};


#endif //RASTERGRAPHICS_IMAGE_H
