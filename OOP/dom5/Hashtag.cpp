//
// Created by yasen on 7/23/18.
//

#include <cstring>
#include <iostream>
#include "Hashtag.h"
#include "Helper.h"

Hashtag::Hashtag(const char* content) : Word(content) { }

unsigned short Hashtag::similarity(char* searchedWord) {
    if(searchedWord[0] == '#') {
        char* contentToLower = Helper::ToLower(getContent());
        char* searchedWordToLower = Helper::ToLower(searchedWord);

        if(!strcmp(contentToLower, searchedWordToLower)) {
            delete[] contentToLower;
            delete[] searchedWordToLower;
            return 100;
        } else {
            delete[] contentToLower;
            delete[] searchedWordToLower;
            return 0;
        }

    } else {
        return 0;
    }
}

Word* Hashtag::clone() {
    return new Hashtag(*this);
}
