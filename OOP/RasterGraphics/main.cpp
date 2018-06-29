#include <iostream>
#include <cstring>
#include "GraphicsApp.h"

int main() {
    GraphicsApp app;
    char command[1024];
    char files[1024];
    while(true) {
        std::cin >> command;
        if(strcmp(command, "load") == 0) {
            std::cin.getline(files, 1024);
            std::cout << files << std::endl;
            app.createSession(files);
        }
        if(strcmp(command, "add") == 0) {
            char file[1024];
            std::cin >> file;
            app.getCurrentSession()->add(file);
        }
        if(strcmp(command, "session") == 0) {
            std::cin >> command;
            if(strcmp(command, "info") == 0) {
                app.getCurrentSession()->listImages();
            }
        }
        if(strcmp(command, "grayscale") == 0) {
            std::cout << "Current session id: " << app.getCurrentSession()->getId() << std::endl;
            app.getCurrentSession()->grayScale();
        }
        if(strcmp(command, "monochrome") == 0) {
            std::cout << "Current session id: " << app.getCurrentSession()->getId() << std::endl;
            app.getCurrentSession()->monoChrome();
        }
        if(strcmp(command, "negative") == 0) {
            std::cout << "Current session id: " << app.getCurrentSession()->getId() << std::endl;
            app.getCurrentSession()->negative();
        }
        if(strcmp(command, "rotate") == 0) {
            std::cin >> command;

            if(strcmp(command, "left") == 0) {
                std::cout << "Current session id: " << app.getCurrentSession()->getId() << std::endl;
                app.getCurrentSession()->rotateLeft();
            }
            if(strcmp(command, "right") == 0) {
                std::cout << "Current session id: " << app.getCurrentSession()->getId() << std::endl;
                app.getCurrentSession()->rotateRight();
            }
        }
        if(strcmp(command, "undo") == 0) {
            app.getCurrentSession()->undo();
        }
        if(strcmp(command, "save") == 0) {
            app.getCurrentSession()->save();
        }

        if(strcmp(command, "exit") == 0) {
            break;
        }
    }
    app.listSessions();

    return 0;
}