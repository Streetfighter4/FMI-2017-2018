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
            if(currentSession != nullptr) {
                currentSession->add(file);
                std::cout << "Image " << file << " has been added!" << std::endl;
            }
        }
        if(strcmp(command, "session") == 0) {
            std::cin >> command;
            if(strcmp(command, "info") == 0) {
                if(currentSession != nullptr)
                    currentSession->listImages();
            }
        }
        if(strcmp(command, "grayscale") == 0) {
            if(currentSession != nullptr){
                currentSession->grayScale();
                std::cout << "Make grayscale!" << std::endl;
            }
        }
        if(strcmp(command, "monochrome") == 0) {
            if(currentSession != nullptr) {
                currentSession->monoChrome();
                std::cout << "Make monoChrome!" << std::endl;
            }
        }
        if(strcmp(command, "negative") == 0) {
            if(currentSession != nullptr) {
                currentSession->negative();
                std::cout << "Make negative!" << std::endl;
            }
        }
        if(strcmp(command, "rotate") == 0) {
            std::cin >> command;

            if(strcmp(command, "left") == 0) {
                if(currentSession != nullptr) {
                    currentSession->rotateLeft();
                    std::cout << "Make rotate left!" << std::endl;
                }
            }
            if(strcmp(command, "right") == 0) {
                if(currentSession != nullptr) {
                    currentSession->rotateRight();
                    std::cout << "Make rotate right!" << std::endl;
                }
            }
        }
        if(strcmp(command, "undo") == 0) {
            if(currentSession != nullptr) {
                currentSession->undo();
                std::cout << "Make undo!" << std::endl;
            }
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
        if(strcmp(command, "listSessions") == 0) {
            app.listSessions();
        }
        if(strcmp(command, "exit") == 0) {
            std::cout << "Bye bye" << std::endl;
            break;
        }
    }
    return 0;
}