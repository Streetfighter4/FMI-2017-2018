//
// Created by yasen on 10/20/18.
//

#ifndef HW1_STUDENT_H
#define HW1_STUDENT_H

#include <ostream>

struct Student {
    char* name;
    char* uni;
    Student();
    Student(const char*, const char*);
    Student&operator=(const Student&);
    ~Student();

    void clear();
    void copy(const Student&);

    friend std::ostream& operator<<(std::ostream& os, const Student& obj);
    friend bool operator==(const Student&, const Student&);
};


#endif //HW1_STUDENT_H
