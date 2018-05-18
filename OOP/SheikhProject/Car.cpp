//
// Created by yasen on 5/2/18.
//
#include <string.h>
#include "Car.h"

Car::Car(char *mark, char *model, unsigned int price) {

    this->mark = new char[strlen(mark)+1];
    strcpy(this->mark, mark);

    this->model = new char[strlen(model)+1];
    strcpy(this->model, model);

    this->price = price;
}

Car::Car(const Car &other) {
    copyFrom(other);
}

Car &Car::operator=(const Car &other) {
    if(this != &other) {
        delete[] mark;
        delete[] model;
        copyFrom(other);
    }

    return *this;
}

void Car::copyFrom(const Car &other) {
    if(other.model) {
        size_t len = strlen(other.model) + 1;
        model = new char[len];
        strcpy(model, other.model);
    }

    if(other.mark) {
        size_t len = strlen(other.mark) + 1;
        mark = new char[len];
        strcpy(mark, other.mark);
    }

    this->price = other.price;
}

Car::~Car() {
    delete[] mark;
    delete[] model;
}
