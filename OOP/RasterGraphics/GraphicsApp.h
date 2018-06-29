//
// Created by yasen on 6/26/18.
//

#ifndef RASTERGRAPHICS_GRAPHICSAPP_H
#define RASTERGRAPHICS_GRAPHICSAPP_H


#include <stdlib.h>
#include "Session.h"

class GraphicsApp {
    Session** sessions;
    size_t countSessions;
public:
    void createSession(char* files);
    void listSessions();
    Session* getCurrentSession();
public:
    GraphicsApp();
    ~GraphicsApp();
};


#endif //RASTERGRAPHICS_GRAPHICSAPP_H
