//
// Created by yasen on 7/23/18.
//

#ifndef DOM5_WORD_H
#define DOM5_WORD_H


class Word {
    char* content;
public:
    Word();
    Word(const char* newContent);
    ~Word();

public:
    inline char* getContent() const { return content; }
    virtual unsigned short similarity(char* searchedWord) = 0;
    virtual Word* clone() = 0;
};


#endif //DOM5_WORD_H
