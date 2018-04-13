//
// Created by yasen on 4/3/18.
//

#ifndef HM2_LINE_H
#define HM2_LINE_H


#include <iostream>
#include "Word.h"

class Line {
    size_t id;
    size_t countWords;
    Word* words;
    bool isHeading;
public:
    Line();
    Line(size_t id, char* content);
    Line& operator=(const Line&);
    ~Line();

    bool isHeadingLine() const;
    void makeHeading();
    void makeItalic(size_t from, size_t to);
    void makeBold(size_t from, size_t to);
    void makeCombine(size_t from, size_t to);
    const Word getWord(size_t index) const;
    const char* getValueWord(size_t index) const;
    void setWord(size_t index, Word& word);
    size_t getCntWords() const;
};


#endif //HM2_LINE_H
