#include <iostream>
#include <cstring>
#include "GraphicsApp.h"

int main() {
    GraphicsApp app;
    char command[1024];
    char files[1024];
    for (int i = 0; i < 5; ++i) {
        std::cin >> command;
        if(strcmp(command, "load") == 0) {
            std::cin.getline(files, 1024);
            std::cout << files << std::endl;
            app.createSession(files);
        }
    }
    app.listSessions();

    return 0;
}