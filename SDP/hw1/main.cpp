#include <iostream>
#include <cstring>
#include "LinkedList.hpp"
#include "DynamicArray.hpp"
#include "Student.h"

int main() {
    DynamicArray<LinkedList<Student*>*> collection;
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
            Student* newStudent = new Student(name, uni);
            if(indexQ1 >= collection.getSize()) {
                LinkedList<Student*>* newQ = new LinkedList<Student*>;
                newQ->push_back(newStudent);
                collection.push_back(newQ);
            } else {
                if(Helper::isCompatible(collection[indexQ1]->back()->uni, newStudent->uni)) {
                    collection[indexQ1]->push_back(newStudent);
                } else {
                    std::cout << "Incompatible people!\n" << std::endl;
                }
            }
            continue;
        }
        if(strcmp(command, "removeLast") == 0) {
            std::cin >> indexQ1;
            if(indexQ1 >= collection.getSize()) {
                std::cout << "Invalid index of queue!\n" << std::endl;
                continue;
            }
            collection[indexQ1]->pop_back();
        }
        if(strcmp(command, "removeFirst") == 0) {
            std::cin >> indexQ1;
            if (indexQ1 >= collection.getSize()) {
                std::cout << "Invalid index of queue!\n" << std::endl;
                continue;
            }
            collection[indexQ1]->pop_front();
        }
        if(strcmp(command, "remove") == 0) {
            std::cin >> name;
            std::cin >> indexQ1;
            if (indexQ1 >= collection.getSize()) {
                std::cout << "Invalid index of queue!\n" << std::endl;
                continue;
            }
            Student* s = new Student(name, uni);
            int index = collection[indexQ1]->search(s);
            delete s;
            if(index == -1) {
                std::cout << "Student not found in this queue :/" << std::endl;
                continue;
            }
            if(index == 0) {
                collection[indexQ1]->pop_front();
                continue;
            }
            if(index == collection[indexQ1]->getSize()-1) {
                collection[indexQ1]->pop_back();
                continue;
            }
            LinkedList<Student*>* newQ = new LinkedList<Student*>;
            *newQ = *collection[indexQ1];
            for (int i = 0; i < collection[indexQ1]->getSize()-index+1; ++i) {
                collection[indexQ1]->pop_back();
            }
            for (int j = 0; j < index+1; ++j) {
                newQ->pop_front();
            }
            collection.push_back(newQ);
        }
        if(strcmp(command, "merge") == 0) {
            std::cin >> indexQ1 >> indexQ2;
            if (indexQ1 >= collection.getSize() || indexQ2 >= collection.getSize()) {
                std::cout << "Invalid index of queue!\n" << std::endl;
                continue;
            }
            if(!Helper::isCompatible(collection[indexQ1]->back()->uni, collection[indexQ2]->front()->uni)) {
                std::cout << "Incompatible people!\n" << std::endl;
                continue;
            }

            size_t sizeQ2 = collection[indexQ2]->getSize();
            for (int i = 0; i < sizeQ2; ++i) {
                collection[indexQ1]->push_back(collection[indexQ2]->front());
                collection[indexQ2]->pop_front();
            }
            delete collection[indexQ2];
            collection.removeAt(indexQ2);
        }
        if(strcmp(command, "exit") == 0) {
            break;
        }
    }


    return 0;
}