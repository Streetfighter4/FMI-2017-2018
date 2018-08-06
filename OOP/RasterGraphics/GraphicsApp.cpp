//
// Created by yasen on 6/26/18.
//

#include <iostream>
#include <cstring>
#include "GraphicsApp.h"

GraphicsApp::GraphicsApp(): sessions(0) {}


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
    Session* session = new Session(sessions.getSize()+1, files, i);

    sessions.push_back(session);

    return session;
}

void GraphicsApp::listSessions() {
    std::cout << "Sessions ids:" << std::endl;
    for (int i = 0; i < sessions.getSize(); ++i) {
        std::cout << "id: " << sessions[i]->getId() << std::endl;
    }
}

Session* GraphicsApp::getSessionById(size_t id) {
    for (int i = 0; i < sessions.getSize(); ++i) {
        if(sessions[i]->getId() == id) {
            return sessions[i];
        }
    }
    return nullptr;
}

