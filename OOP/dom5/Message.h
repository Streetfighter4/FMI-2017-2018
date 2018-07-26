//
// Created by yasen on 7/23/18.
//

#ifndef DOM5_MESSAGE_H
#define DOM5_MESSAGE_H


#include <cstdlib>
#include "Word.h"

class Message {
    char* content;
    Word** words;
    size_t countWords;
private:
    void copy(const Message&);
public:
    Message();
    Message(const Message&);
    explicit Message(const char* content);
    ~Message();

public:
    inline char* getContent() const { return content; }
    void findHashtags();
    unsigned short countScore(char* searchedWord);
    unsigned short countMessageScore(const char* searchedMessage);
};


#endif //DOM5_MESSAGE_H
