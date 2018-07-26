//
// Created by yasen on 7/23/18.
//

#ifndef DOM5_HASHTAG_H
#define DOM5_HASHTAG_H


#include "Word.h"

class Hashtag : public Word {
public:
    explicit Hashtag(const char* content);

    unsigned short similarity(char* searchedWord) override;
    Word* clone() override;
};


#endif //DOM5_HASHTAG_H
