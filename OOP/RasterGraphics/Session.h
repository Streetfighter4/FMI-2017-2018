//
// Created by yasen on 6/26/18.
//

#ifndef RASTERGRAPHICS_SESSION_H
#define RASTERGRAPHICS_SESSION_H


#include "Image.h"

class Session {
    size_t id;
    Image** images;
    size_t countImages;

    void copy(const Session&);
public:
    void grayScale();
    void monoChrome();
    void negative();
    void rotateLeft();
    void rotateRight();
    void undo();
    void add(size_t id, char* filename);
    void save();
public:
    Session(size_t id);
    Session&operator=(const Session&);
    ~Session();
};


#endif //RASTERGRAPHICS_SESSION_H
