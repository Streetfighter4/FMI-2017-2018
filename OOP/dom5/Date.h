//
// Created by yasen on 7/23/18.
//

#ifndef DOM5_DATE_H
#define DOM5_DATE_H


#include "Word.h"

class Date : public Word {
public:
    explicit Date(const char* content);

public:
    unsigned short similarity(char* searchedWord) override;
    Word* clone() override;
};


#endif //DOM5_DATE_H
