//
// Created by yasen on 6/28/18.
//

#ifndef RASTERGRAPHICS_IMAGEPGM_H
#define RASTERGRAPHICS_IMAGEPGM_H


#include "Image.h"

class ImagePGM : Image {
private:
    size_t maxValueOfWhite;
public:
    ImagePGM(char *filename);

public:

};


#endif //RASTERGRAPHICS_IMAGEPGM_H
