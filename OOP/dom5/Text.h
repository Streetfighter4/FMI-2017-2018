//
// Created by yasen on 7/23/18.
//

#ifndef DOM5_TEXT_H
#define DOM5_TEXT_H


#include <cstdlib>
#include "Message.h"

class Text {
    Message** messages;
    size_t countMessages;
private:
    void resize();
public:
    Text(const char* filename);
    Text(const Text& other);
    ~Text();

public:
    void findHashtags();
    void findMessage(char* searchedWord);
    void sortMessages(char* searchedWord);
    void listMessages();
public:
    Text& operator+=(const char* message);
    Text operator+(const char* message) const;
    Message& operator[](const char* message);
};


#endif //DOM5_TEXT_H
