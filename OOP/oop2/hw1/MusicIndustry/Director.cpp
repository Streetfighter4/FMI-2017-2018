//
// Created by yasen on 3/28/19.
//

#include "Director.h"

Director::Director(const char *new_name, unsigned int new_age) : age(new_age){
    name = new char[strlen(new_name)+1];
    strcpy(name, new_name);
}

Director::~Director() {
    delete[] name;
}

