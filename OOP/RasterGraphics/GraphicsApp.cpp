//
// Created by yasen on 6/26/18.
//

#include <iostream>
#include <cstring>
#include "GraphicsApp.h"

GraphicsApp::GraphicsApp(): sessions(nullptr), countSessions(0) {}

GraphicsApp::~GraphicsApp() {
    for (int i = 0; i < countSessions; ++i) {
        delete sessions[i];
    }
    delete[] sessions;
}

Session* GraphicsApp::createSession(char* files) {
    char* buff = new char[strlen(files)+1];
    strcpy(buff, files);
    char* pch;
    int i = 0;
    pch = strtok (buff," ");
    while (pch != nullptr) {
        pch = strtok (nullptr, " ");
        i++;
    }
    delete[] buff;
    Session* session = new Session(countSessions+1, files, i);

    Session** temp = new Session*[countSessions+1];

    for (size_t i = 0; i < countSessions; i++) {
        temp[i] = sessions[i];
    }
    temp[countSessions] = session;

    ++countSessions;
    delete[] sessions;
    sessions = temp;
    return session;
}

void GraphicsApp::listSessions() {
    std::cout << "Sessions ids:" << std::endl;
    for (int i = 0; i < countSessions; ++i) {
        std::cout << "id: " << sessions[i]->getId() << std::endl;
    }
}

Session* GraphicsApp::getSessionById(size_t id) {
    for (int i = 0; i < countSessions; ++i) {
        if(sessions[i]->getId() == id) {
            return sessions[i];
        }
    }
    return nullptr;
}

