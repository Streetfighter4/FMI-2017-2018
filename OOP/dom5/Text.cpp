//
// Created by yasen on 7/23/18.
//

#include "Text.h"
#include "Helper.h"
#include <iostream>
#include <fstream>

Text::Text(const char* filename) {
    std::ifstream ifs(filename);
    const LINE_LENGTH = 280;
    char line[LINE_LENGTH] = { 0 };
    countMessages = 0;
    while (!ifs.eof()) {

        ifs.getline(line, LINE_LENGTH);

        if(ifs) {
            countMessages++;
        }

        memset(line, 0, LINE_LENGTH);
    }
    ifs.clear(); //re-setting flag as EOF
    ifs.seekg(0, std::ios::beg);

    messages = new Message*[countMessages+1];
    int i = 0;
    while (!ifs.eof()) {

        ifs.getline(line, LINE_LENGTH);

        if (ifs) {
            messages[i++] = new Message(line);
        }

        memset(line, 0, LINE_LENGTH);
    }

    ifs.close();
}

Text::Text(const Text& other) : countMessages(other.countMessages), messages(new Message*[other.countMessages]) {
    for (int i = 0; i < countMessages; ++i) {
        messages[i] = new Message(*other.messages[i]);
    }
}

Text::~Text() {
    for (int i = 0; i < countMessages; ++i) {
        delete messages[i];
    }

    delete[] messages;
}

void Text::findHashtags() {
    for (int i = 0; i < countMessages; ++i) {
        messages[i]->findHashtags();
    }
}

void Text::findMessage(char* searchedWord) {
    unsigned int currentMessageScore = 0;
    unsigned int bestMessageScore = 0;
    int bestMessageId = -1;
    for (int i = 0; i < countMessages; ++i) {
        currentMessageScore = messages[i]->countScore(searchedWord);
        if(currentMessageScore > bestMessageScore) {
            bestMessageScore = currentMessageScore;
            bestMessageId = i;
        }
    }
    std::cout << messages[bestMessageId]->getContent() << std::endl;
}

void Text::sortMessages(char* searchedWord) {
    unsigned short* messagesScores = new unsigned short[countMessages];
    unsigned short* messagesId = new unsigned short[countMessages];

    for (int i = 0; i < countMessages; ++i) {
        messagesScores[i] = messages[i]->countScore(searchedWord);
        messagesId[i] = i;
    }

    for (int j = 0; j < countMessages-1; ++j) {
        for (int k = j; k < countMessages; ++k) {
            if(messagesScores[j] < messagesScores[k]) {
                unsigned short buff = messagesScores[j];
                messagesScores[j] = messagesScores[k];
                messagesScores[k] = buff;

                unsigned short idBuff = messagesId[j];
                messagesId[j] = messagesId[k];
                messagesId[k] = idBuff;
            }
        }
    }
    delete[] messagesScores;
    for (int l = 0; l < countMessages; ++l) {
        std::cout << messages[messagesId[l]]->getContent() << std::endl;
    }
    delete[] messagesId;
}

void Text::resize() {
    if (messages == nullptr) {

        messages = new Message*[countMessages+1];
        ++countMessages;
    } else {
        Message** newMessages = new Message*[countMessages+1];
        for (int j = 0; j < countMessages; ++j) {
            newMessages[j] = messages[j];
        }

        delete[] messages;
        messages = newMessages;
    }
}

Text& Text::operator+=(const char* message) {
    resize();
    messages[countMessages] = new Message(message);
    ++countMessages;

    return *this;
}

Text Text::operator+(const char* message) const {
    Text text(*this);
    text += message;

    return text;
}

Message& Text::operator[](const char* message) {
    unsigned short messageScore = 0;
    unsigned short bestMessageScore = 0;
    short bestMessageId = -1;
    for (int i = 0; i < countMessages; ++i) {
        messageScore = messages[i]->countMessageScore(message);
        //std::cout << "message[" << i << "] with score: " << messageScore << std::endl;
        if(messageScore > bestMessageScore) {
            bestMessageScore = messageScore;
            bestMessageId = i;
        }
    }
    return *messages[bestMessageId];
}

void Text::listMessages() {
    for (int i = 0; i < countMessages; ++i) {
        std::cout << i << ":" << messages[i]->getContent() << std::endl;
    }
}

