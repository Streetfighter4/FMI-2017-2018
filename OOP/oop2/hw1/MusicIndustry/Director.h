//
// Created by yasen on 3/28/19.
//

#ifndef MUSICINDUSTRY_DIRECTOR_H
#define MUSICINDUSTRY_DIRECTOR_H

#include <string.h>

class Director {
    char* name;
    unsigned int age;
public:
    Director(const char* new_name, unsigned int new_age);
    Director(const Director&) = delete;
    Director&operator=(const Director&) = delete;
    ~Director();

public:
    inline unsigned int getAge() const { return age; }
    inline const char* getName() const { return name; }

};


#endif //MUSICINDUSTRY_DIRECTOR_H
