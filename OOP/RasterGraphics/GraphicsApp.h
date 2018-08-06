//
// Created by yasen on 6/26/18.
//

#ifndef RASTERGRAPHICS_GRAPHICSAPP_H
#define RASTERGRAPHICS_GRAPHICSAPP_H


#include <stdlib.h>
#include "Session.h"

class GraphicsApp {
    Conteiner<Session*> sessions;
public:
    Session* createSession(char* files);
    void listSessions();
    Session* getSessionById(size_t id);
public:
    GraphicsApp();
    ~GraphicsApp() = default;
};


#endif //RASTERGRAPHICS_GRAPHICSAPP_H
