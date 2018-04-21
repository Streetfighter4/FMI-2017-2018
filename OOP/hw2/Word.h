//
// Created by yasen on 4/3/18.
//

#ifndef HM2_WORD_H
#define HM2_WORD_H

#include <iostream>

class Word {
    size_t id;
    char* value;
    bool isBold;
    bool isItalic;
public:
    Word();
    Word(size_t id, char* value);
    Word&operator=(const Word&);
    ~Word();

    const char* getValue() const;

    bool getIsBold() const;
    bool getIsItalic() const;

    void setIsBold(bool isBold);
    void setIsItalic(bool isItalic);
};

#endif //HM2_WORD_H
