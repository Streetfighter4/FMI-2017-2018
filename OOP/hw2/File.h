//
// Created by yasen on 4/3/18.
//

#ifndef HM2_FILE_H
#define HM2_FILE_H

#include "Line.h"
#include <iostream>
#include <fstream>
using std::ifstream;

class File {
    char* name;
    ifstream file;
    Line** lines;
    size_t cntLines;
    size_t countLines();
public:
    File();
    File(const char *name, size_t countLines);
    ~File();

    bool parser();
    void makeChanges();
    void addLine(char* content);
    void removeLine(size_t index);
    void exit();
};


#endif //HM2_FILE_H
