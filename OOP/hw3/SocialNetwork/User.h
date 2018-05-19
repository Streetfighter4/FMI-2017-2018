//
// Created by yasen on 5/17/18.
//

#ifndef SOCIALNETWORK_USER_H
#define SOCIALNETWORK_USER_H


#include <iostream>
#include "Post.h"

class User {
    Post* createPost(const char* type);
    void clear();
public:

    User(const char* nickname, unsigned short age, unsigned long long id);
    User(const User&) = delete;
    User&operator=(const User&);
    ~User();

    unsigned long long id;
    char* nickName;
    unsigned short age;
    bool isBlocked;
    Post** posts;
    size_t countPost;

    void changeNickName(const char* newNickName);
    void addPost(Post* post);
};


#endif //SOCIALNETWORK_USER_H
