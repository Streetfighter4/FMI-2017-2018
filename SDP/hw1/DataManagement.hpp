//
// Created by yasen on 10/22/18.
//

#ifndef HW1_DATAMANAGEMENT_HPP
#define HW1_DATAMANAGEMENT_HPP


#include "Student.h"
#include "LinkedList.hpp"
#include "DynamicArray.hpp"
#include <fstream>

bool isCompatible(const char* uni1, const char* uni2) {
    if (strcmp(uni1, uni2) == 0) {
        return true;
    }
    if (strcmp(uni2, "fmi") == 0) {
        return strcmp(uni1, "tu") == 0;
    }
    if (strcmp(uni2, "tu") == 0) {
        return strcmp(uni1, "unss") == 0;
    }
    if (strcmp(uni2, "unss") == 0) {
        return strcmp(uni1, "fmi") == 0;
    }
}

void append(unsigned short indexQ1, char* name, char* uni, DynamicArray<LinkedList < Student *>*>& collection) {
    Student* newStudent = new Student(name, uni);
    if(indexQ1 >= collection.getSize()) {
        LinkedList<Student*>* newQ = new LinkedList<Student*>;
        newQ->push_back(newStudent);
        collection.push_back(newQ);
    } else {
        if(isCompatible(collection[indexQ1]->back()->uni, newStudent->uni)) {
            collection[indexQ1]->push_back(newStudent);
        } else {
            std::cout << "Incompatible people!\n" << std::endl;
        }
    }
}

void setData(DynamicArray<LinkedList<Student*>*>& collection, char* file) {
    char command[8];
    char name[128];
    char uni[4];
    unsigned short indexQ;

    std::ifstream ifile;
    ifile.open(file);
    if(ifile.is_open()) {
        while(!ifile.eof()) {
            ifile >> command >> name >> uni >> indexQ;
            if(ifile.eof()) {
                break;
            }
            if(command) {
                append(indexQ, name, uni, collection);
            }

            memset(command, 0, 8);
            memset(name, 0, 128);
            memset(uni, 0, 4);
        }

        ifile.close();
    }
}

#endif //HW1_DATAMANAGEMENT_HPP
