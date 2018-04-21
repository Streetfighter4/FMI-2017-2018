//
// Created by yasen on 4/3/18.
//

#ifndef HM2_FILE_H
#define HM2_FILE_H

#include "Line.h"
#include <iostream>

class File {
    char* name;
    Line** lines;
    size_t cntLines;
public:
    File();
    File(const char* name, size_t countLines);
    ~File();

    bool validInput(int, int=1, int=2);
    bool parser();
    void makeChanges();
    void addLine(char* content);
    void removeLine(size_t index);
    void exit();

    bool hasSpace(size_t i, size_t j) const;
};


#endif //HM2_FILE_H
