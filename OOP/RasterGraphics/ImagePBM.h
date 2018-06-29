//
// Created by yasen on 6/28/18.
//

#ifndef RASTERGRAPHICS_IMAGEPBM_H
#define RASTERGRAPHICS_IMAGEPBM_H


#include "Image.h"

class ImagePBM : public Image {
    void negative();
public:
    ImagePBM(char *filename);
    ImagePBM(const ImagePBM&);
public:
    virtual void parse(char* filename);
    virtual Image* clone();
    virtual void save();
};


#endif //RASTERGRAPHICS_IMAGEPBM_H
