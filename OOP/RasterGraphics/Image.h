//
// Created by yasen on 6/26/18.
//

#ifndef RASTERGRAPHICS_IMAGE_H
#define RASTERGRAPHICS_IMAGE_H

#include "Command.h"
#include "Conteiner.h"

class Image {
protected:
    char* filename;
    size_t width;
    size_t height;
    int** data;
public:

    Conteiner<COMMAND> commands;
public:

    Image(char* filename);
    Image& operator=(const Image&) = delete;
    Image(const Image&);
    ~Image();

    inline char* getName() { return filename; }
    void listCommands();
    virtual void parse(char* filename) = 0;
    virtual Image* clone() = 0;
    virtual void save() = 0;
//    virtual void free() = 0;
};


#endif //RASTERGRAPHICS_IMAGE_H
