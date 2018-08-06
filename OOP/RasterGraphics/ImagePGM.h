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
    void writeInFile(char* filename);
public:
    explicit ImagePGM(char* filename);
    ImagePGM(const ImagePGM&);
public:
    void parse(char* filename) override;
    void save() override;
};


#endif //RASTERGRAPHICS_IMAGEPGM_H
