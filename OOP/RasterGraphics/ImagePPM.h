//
// Created by yasen on 6/28/18.
//

#ifndef RASTERGRAPHICS_IMAGEPPM_H
#define RASTERGRAPHICS_IMAGEPPM_H


#include "Image.h"

class ImagePPM : public Image {
    size_t maxValueOfPixel;
    bool isGrayScale;
    void grayScale();
    void monoChrome();
    void negative();
public:
    ImagePPM(char* filename);
    ImagePPM(const ImagePPM&);
public:
    virtual void parse(char* filename);
    virtual Image* clone();
    virtual void save();
};


#endif //RASTERGRAPHICS_IMAGEPPM_H
