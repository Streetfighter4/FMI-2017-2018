//
// Created by yasen on 7/23/18.
//

#include <ctime>
#include <cstring>
#include <iostream>
#include "Simple.h"

Simple::Simple(const char* content) : Word(content) { }

unsigned short int Simple::similarity(char* searchedWord) {
    struct tm tm;
    if(searchedWord[0] == '#') {
        return 0;
    } else if(strptime(searchedWord, "%d-%m-%Y", &tm)) {
        return 0;
    } else {
        size_t contentLength = strlen(getContent());
        size_t searchedWordLength = strlen(searchedWord);

        size_t smallerLength = (contentLength < searchedWordLength) ? contentLength : searchedWordLength;
        size_t largerLength = (contentLength > searchedWordLength) ? contentLength : searchedWordLength;
        size_t score = 0;
        for (int i = 0; i < smallerLength; ++i) {
            if(getContent()[i] == searchedWord[i]) {
                score++;
            }
        }

        double coff = (double)score/largerLength;
        return static_cast<unsigned short>(coff*100);
    }

}

Word* Simple::clone() {
    return new Simple(*this);
}
