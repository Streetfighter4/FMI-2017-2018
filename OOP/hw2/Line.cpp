//
// Created by yasen on 4/3/18.
//
#include <iostream>
#include <string.h>
#include "Line.h"

using std::cout;
using std::endl;

Line::Line() {
}

Line::Line(size_t id, char* content) : id(id), isHeading(false) {
    char* token;
    token = strtok(content, " ");
    size_t i = 1;
    Word* tempWords = new Word[512];
    while(token != nullptr) {
        Word* word = new Word(i, token);
        tempWords[i-1] = *word;
        token = strtok(nullptr, " ");
        ++i;
    }

    countWords = i - 1;
    words = new Word[countWords];

    for (int j = 0; j < countWords; ++j) {
        words[j] = tempWords[j];
    }

    delete[] tempWords;
}

Line::~Line() {
    delete[] words;
}

bool Line::isHeadingLine() const {
    return isHeading;
}

const Word& Line::getWord(size_t index) const {
    return words[index];
}

const char* Line::getValueWord(size_t index) const {
    return words[index].getValue();
}

void Line::makeHeading() {
    isHeading = true;
}

void Line::makeItalic(size_t from, size_t to) {
    for (size_t i = from; i <= to; ++i) {
        words[i].setIsItalic(true);
    }
}

void Line::makeBold(size_t from, size_t to) {
    for (size_t i = from; i <= to; ++i) {
        words[i].setIsBold(true);
    }
}

void Line::makeCombine(size_t from, size_t to) {
    for (size_t i = from; i <= to; ++i) {
        words[i].setIsItalic(true);
        words[i].setIsBold(true);
    }
}

Line& Line::operator=(const Line& other) {
    if(this != &other) {
        id = other.id;
        isHeading = other.isHeading;

        Word* tempWords = new Word[other.countWords];
        for (int i = 0; i < other.countWords; ++i) {
            tempWords[i] = other.words[i];
        }
        delete[] words;
        this->words = tempWords;

        countWords = other.countWords;
    }

    return *this;
}

size_t Line::getCntWords() const {
    return countWords;
}
