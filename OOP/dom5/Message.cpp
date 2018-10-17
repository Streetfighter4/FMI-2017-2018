//
// Created by yasen on 7/23/18.
//

#include "Message.h"
#include "Helper.h"
#include <iostream>
Message::Message() : content(nullptr), words(nullptr), countWords(0) {}

Message::Message(const Message& other) {
    copy(other);
}

Message::Message(const char* newContent) {
    content = new char[strlen(newContent)+1];
    strcpy(content, newContent);

    countWords = Helper::countWords(content);
    words = new Word*[countWords];

    size_t startIndex = 0;
    size_t endIndex = 0;
    char* token;
    size_t i = 0;

    do {
        endIndex++;
        if(content[endIndex] == '\0' || (Helper::isSeparator(content[endIndex]) && !Helper::isSeparator(content[endIndex-1]))) {
            size_t tokenLength = endIndex - startIndex;
            token = new char[tokenLength];
            strncpy(token, content+startIndex, tokenLength);
            token[tokenLength] = '\0';
            std::cout << "token: " << token << std::endl;
            words[i++] = Helper::createWord(token);
            startIndex = endIndex+1;
        }
        if(Helper::isSeparator(content[endIndex]) && Helper::isSeparator(content[endIndex-1])) {
            startIndex++;
        }

    } while(content[endIndex]);

}

Message::~Message() {
    delete[] content;
    for (int i = 0; i < countWords; ++i) {
        delete words[i];
    }

    delete[] words;
}

void Message::findHashtags() {
    for (int i = 0; i < countWords; ++i) {
        if(words[i]->getContent()[0] == '#') {
            std::cout << words[i]->getContent() << std::endl;
        }
    }
}

unsigned short Message::countScore(char* searchedWord) {
    unsigned short currentMessageScore = 0;

    for (int i = 0; i < countWords; ++i) {
        currentMessageScore += words[i]->similarity(searchedWord);
    }
    return currentMessageScore;
}

unsigned short Message::countMessageScore(const char *searchedMessage) {
    Message* messageObj = new Message(searchedMessage);
    unsigned short currentMessageScore = 0;
    for (int i = 0; i < messageObj->countWords; ++i) {
        currentMessageScore += countScore(messageObj->words[i]->getContent());
    }
    return currentMessageScore;
}


void Message::copy(const Message& other) {
    content = new char[strlen(other.content)+1];
    strcpy(content, other.content);

    words = new Word*[other.countWords];
    for (int i = 0; i < other.countWords; ++i) {
        words[i] = other.words[i]->clone();
    }

    countWords = other.countWords;
}

