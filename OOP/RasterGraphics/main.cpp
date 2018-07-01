#include <iostream>
#include <cstring>
#include "GraphicsApp.h"

int main() {
    GraphicsApp app;
    Session* currentSession = nullptr;
    char command[1024];
    char files[1024];
    while(true) {
        std::cin >> command;
        if(strcmp(command, "load") == 0) {
            std::cin.getline(files, 1024);
            currentSession = app.createSession(files);
            std::cout << "Session with id " << currentSession->getId() << " has been created!" << std::endl;
        }
        if(strcmp(command, "add") == 0) {
            char file[1024];
            std::cin >> file;
            if(currentSession != nullptr)
                currentSession->add(file);
        }
        if(strcmp(command, "session") == 0) {
            std::cin >> command;
            if(strcmp(command, "info") == 0) {
                if(currentSession != nullptr)
                    currentSession->listImages();
            }
        }
        if(strcmp(command, "grayscale") == 0) {
            if(currentSession != nullptr)
                currentSession->grayScale();
        }
        if(strcmp(command, "monochrome") == 0) {
            if(currentSession != nullptr)
                currentSession->monoChrome();
        }
        if(strcmp(command, "negative") == 0) {
            if(currentSession != nullptr)
                currentSession->negative();
        }
        if(strcmp(command, "rotate") == 0) {
            std::cin >> command;

            if(strcmp(command, "left") == 0) {
                if(currentSession != nullptr)
                    currentSession->rotateLeft();
            }
            if(strcmp(command, "right") == 0) {
                if(currentSession != nullptr)
                    currentSession->rotateRight();
            }
        }
        if(strcmp(command, "undo") == 0) {
            if(currentSession != nullptr)
                currentSession->undo();
        }
        if(strcmp(command, "save") == 0) {
            if(currentSession != nullptr) {
                currentSession->save();
                std::cout << "Save images in current session!" << std::endl;
            }
        }
        if(strcmp(command, "switch") == 0) {
            size_t id;
            std::cin >> id;
            if(app.getSessionById(id) != nullptr) {
                currentSession = app.getSessionById(id);
                std::cout << "You switched to session with ID: " << currentSession->getId() << std::endl;
            } else {
                std::cerr << "Session with this id doesn't exist" << std::endl;
                std::cerr << "You can use command 'listSessions' for see all sessions" << std::endl;
            }
        }
        if(strcmp(command, "make") == 0) {
            std::cin >> command;
            if(strcmp(command, "collage") == 0) {
                std::cin >> command;
                char file1[1024];
                char file2[1024];
                if(strcmp(command, "horizontal") == 0) {
                    std::cin >> file1 >> file2;
                    currentSession->makeHorizontalCollage(file1, file2);
                }
                if(strcmp(command, "vertical") == 0) {
                    std::cin >> file1 >> file2;
                    currentSession->makeVerticalCollage(file1, file2);
                }
            }
        }
        if(strcmp(command, "listSessions") == 0) {
            app.listSessions();
        }
        if(strcmp(command, "exit") == 0) {
            break;
        }
    }
    return 0;
}