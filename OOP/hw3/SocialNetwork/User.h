//
// Created by yasen on 5/17/18.
//

#ifndef SOCIALNETWORK_USER_H
#define SOCIALNETWORK_USER_H


#include <iostream>
#include "Post.h"

class User {
    void clear();

public:

    User(const char* nickname, unsigned short age, unsigned long long id);
    User(const User&) = delete;
    User&operator=(const User&);
    ~User();

private:
    unsigned long long id;
    char* nickName;
    unsigned short age;
    bool isBlocked;
    size_t countPost;

public:
    Post** posts;

    unsigned long long getId() const;
    char* getNickName() const;
    unsigned short getAge() const;
    bool getIsBloked() const;
    void setIsBloked(bool isBloked);
    size_t getCountPost() const;

    void personalInfo();
    void changeNickName(const char* newNickName);
    void addPost(Post* post);
    void deletePost(unsigned long long id);
};


#endif //SOCIALNETWORK_USER_H
