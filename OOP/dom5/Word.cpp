//
// Created by yasen on 7/23/18.
//

#include <cstring>
#include "Word.h"
Word::Word() : content(nullptr) {}

Word::Word(const char* newContent) {
    content = new char[strlen(newContent) + 1];
    strcpy(content, newContent);
}

Word::~Word() {
    delete[] content;
}

