#include <iostream>
#include <cstring>
#include "LinkedList.h"
#include "DynamicArray.h"
#include "DataManagement.cpp"

int main(int argc, char* argv[]) {
    DynamicArray<LinkedList<Student*>*> collection;
    // If you wont to set fake data
    //setData(collection, argv[1]);

    char command[16];
    char name[128];
    char uni[8];
    unsigned short indexQ1, indexQ2;

    while (true) {
        std::cin >> command;
        if(strcmp(command, "print") == 0) {
            collection.printContent();
            continue;
        }

        if(strcmp(command, "append") == 0) {
            std::cin >> name;
            std::cin >> uni;
            std::cin >> indexQ1;
            append(indexQ1, name, uni, collection);
            continue;
        }
        if(strcmp(command, "removeLast") == 0) {
            std::cin >> indexQ1;
            removeLast(indexQ1, collection);
            continue;
        }
        if(strcmp(command, "removeFirst") == 0) {
            std::cin >> indexQ1;
            removeFirst(indexQ1, collection);
            continue;
        }
        if(strcmp(command, "remove") == 0) {
            std::cin >> name;
            std::cin >> indexQ1;
            remove(indexQ1, name, uni, collection);
            continue;
        }
        if(strcmp(command, "merge") == 0) {
            std::cin >> indexQ1 >> indexQ2;
            merge(indexQ1, indexQ2, collection);
            continue;
        }
        if(strcmp(command, "exit") == 0) {
            break;
        }
    }


    return 0;
}