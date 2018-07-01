//
// Created by yasen on 6/28/18.
//

#ifndef RASTERGRAPHICS_IMAGEPPM_H
#define RASTERGRAPHICS_IMAGEPPM_H


#include "Image.h"

class ImagePPM : public Image {
    size_t maxValueOfPixel;
    bool isGrayScale;
    bool isMonoChrome;
    void grayScale();
    void monoChrome();
    void negative();

    bool isEqual(int, int, int);
    bool isBlackOrWhite(int, int, int);
public:
    ImagePPM(char* filename);
    ImagePPM(const ImagePPM&);
    ~ImagePPM();
public:
    virtual void parse(char* filename);
    virtual Image* clone();
    virtual void save();
    virtual void free();
    virtual void rotateLeft() override;
};


#endif //RASTERGRAPHICS_IMAGEPPM_H
