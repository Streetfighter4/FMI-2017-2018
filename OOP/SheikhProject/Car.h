//
// Created by yasen on 5/2/18.
//

#ifndef SHEIKHPROJECT_CAR_H
#define SHEIKHPROJECT_CAR_H


class Car {
protected:
    char* mark;
    char* model;
    unsigned int price;

    void copyFrom(const Car& other);
public:
    Car(char* mark, char* model, unsigned int price);
    Car(const Car& other);
    Car&operator=(const Car& other);
    ~Car();
};


#endif //SHEIKHPROJECT_CAR_H
