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

    bool isEqual(const size_t&, const size_t&, const size_t&) const;
    bool isBlackOrWhite(const size_t&, const size_t&, const size_t&) const;
    void writeInFile(char* filename) const ;
public:
    explicit ImagePPM(char* filename);
    ImagePPM(const ImagePPM&);
public:
    void parse(char* filename) override;
    void save() override;
};


#endif //RASTERGRAPHICS_IMAGEPPM_H
