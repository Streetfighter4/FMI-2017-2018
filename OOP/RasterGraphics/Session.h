//
// Created by yasen on 6/26/18.
//

#ifndef RASTERGRAPHICS_SESSION_H
#define RASTERGRAPHICS_SESSION_H


#include "Image.h"

class Session {
    size_t id;
    Conteiner<Image*> images;

    void copy(const Session&);
    Image* createImage(char* file);
    char* getExtension(char* filename);
public:
    void grayScale();
    void monoChrome();
    void negative();
    void rotateLeft();
    void rotateRight();
    void undo();
    void add(char* filename);
    void save();
public:
    inline size_t getId() const { return id; }
    void listImages() const;
public:
    Session(size_t id, char* files, size_t countImages);
    Session&operator=(const Session&);
    ~Session() = default;
};


#endif //RASTERGRAPHICS_SESSION_H
