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
    size_t* data;

    void free();
public:

    Conteiner<COMMAND> commands;
public:

    explicit Image(char* filename);
    Image& operator=(const Image&) = delete;
    Image(const Image&);
    ~Image();

    inline const char* getName() const { return filename; }
    void listCommands();
    virtual void parse(char* filename) = 0;
    virtual void save() = 0;
    void rotateLeft();
    void rotateRight();
    void makeRotations(int countRotation);
};


#endif //RASTERGRAPHICS_IMAGE_H
