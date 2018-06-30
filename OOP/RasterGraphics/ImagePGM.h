//
// Created by yasen on 6/28/18.
//

#ifndef RASTERGRAPHICS_IMAGEPGM_H
#define RASTERGRAPHICS_IMAGEPGM_H


#include "Image.h"

class ImagePGM : public Image {
private:
    size_t maxValueOfWhite;
    bool isMonoChrome;
    void monoChrome();
    void negative();
public:
    ImagePGM(char* filename);
    ImagePGM(const ImagePGM&);
    ~ImagePGM();
public:
    void parse(char* filename);
    virtual Image* clone();
    virtual void save();
    virtual void free();
};


#endif //RASTERGRAPHICS_IMAGEPGM_H
