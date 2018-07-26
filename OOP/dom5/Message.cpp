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
    content = new char[strlen(newContent) + 1];
    strcpy(content, newContent);


    char* buff = new char[strlen(newContent)+1];
    strcpy(buff, newContent);

    countWords = 0;

    char* token = strtok (buff," ,._!?");

    while (token != NULL) {
        countWords++;
        token = strtok(NULL, " ,._!?");
    }
    delete[] buff;

    words = new Word*[countWords+1];

    char* buff1 = new char[strlen(newContent)+1];
    strcpy(buff1, newContent);

    int i = 0;
    token = strtok(buff1, " ,._!?");
    while (token != NULL) {
        words[i++] = Helper::createWord(token);
        token = strtok(NULL, " ,._!?");
    }
    delete[] buff1;
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

