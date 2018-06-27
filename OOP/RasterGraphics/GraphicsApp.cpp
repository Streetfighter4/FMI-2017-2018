//
// Created by yasen on 6/26/18.
//

#include "GraphicsApp.h"

GraphicsApp::GraphicsApp(): sessions(nullptr), countSessions(0) {}

GraphicsApp::~GraphicsApp() {
    for (int i = 0; i < countSessions; ++i) {
        delete sessions[i];
    }
    delete[] sessions;
}

void GraphicsApp::createSession() {
    Session* session = new Session(countSessions+1);
    Session** temp = sessions;
    sessions = new Session*[countSessions+1];

    for (size_t i = 0; i < countSessions; i++) {
        sessions[i] = temp[i];
    }
    sessions[countSessions] = session;

    for (int j = 0; j < countSessions; ++j) {
        delete temp[j];
    }
    delete[] temp;

    countSessions++;
}
