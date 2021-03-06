//
// Created by yasen on 6/28/18.
//

#ifndef RASTERGRAPHICS_IMAGEPBM_H
#define RASTERGRAPHICS_IMAGEPBM_H


#include "Image.h"

class ImagePBM : public Image {
    void negative();
    void writeInFile(char* filename);
public:
    explicit ImagePBM(char *filename);
    ImagePBM(const ImagePBM&);
public:
    void parse(char* filename) override;
    void save() override;
};


#endif //RASTERGRAPHICS_IMAGEPBM_H
