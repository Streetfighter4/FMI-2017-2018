//
// Created by yasen on 7/23/18.
//

#ifndef DOM5_SIMPLE_H
#define DOM5_SIMPLE_H


#include "Word.h"

class Simple : public Word {
public:
    explicit Simple(const char* content);

public:
    unsigned short similarity(char* searchedWord) override;
    Word* clone() override;
};


#endif //DOM5_SIMPLE_H
