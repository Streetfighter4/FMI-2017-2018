//
// Created by yasen on 5/17/18.
//

#include <cstring>
#include "User.h"

User::User(const char* nickname, unsigned short age, unsigned long long id) :
        age(age), isBlocked(false), posts(nullptr), countPost(0), id(id) {
    this->nickName = new char[strlen(nickname) + 1];
    strcpy(this->nickName, nickname);
}

User& User::operator=(const User& other) {
    if (this != &other) {
        std::cout << "other.id: " << other.id << std::endl;
        clear();
        this->id = other.id;
        age = other.age;
        isBlocked = other.isBlocked;

        nickName = new char[strlen(other.nickName) + 1];
        strcpy(nickName, other.nickName);

        //posts = new Post* [other.countPost]; // allocating memory for all base pointers

        //for (int i = 0; i < other.countPost; i++)
            //posts[i] = other.posts[i]->clone();

        countPost = other.countPost;
    }

    return *this;
}

User::~User() {
    clear();
}

void User::clear() {
    delete[] nickName;

    for (int i = 0; i < countPost; i++)
        delete posts[i];

    delete[] posts;
}
