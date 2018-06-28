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

void GraphicsApp::createSession(char* files) {
    char* buff = new char[strlen(files)+1];
    strcpy(buff, files);
    char* pch;
    int i = 0;
    pch = strtok (buff," ");
    while (pch != NULL) {
        pch = strtok (NULL, " ");
        i++;
    }
    delete[] buff;
    std::cout << "files1: " << files << std::endl;
    Session* session = new Session(countSessions+1, files, i);

    std::cout << "session id: " << session->getId() << std::endl;
    Session** temp = new Session*[countSessions+1];

    for (size_t i = 0; i < countSessions; i++) {
        temp[i] = sessions[i];
    }
    temp[countSessions] = session;

    ++countSessions;
    delete[] sessions;
    sessions = temp;
}

void GraphicsApp::listSessions() {
    for (int i = 0; i < countSessions; ++i) {
        std::cout << "list session id: " << sessions[i]->getId() << std::endl;
    }
}
