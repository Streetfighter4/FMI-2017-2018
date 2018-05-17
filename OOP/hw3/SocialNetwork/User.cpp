//
// Created by yasen on 5/17/18.
//

#include <cstring>
#include "User.h"

User::User(const char* nickname, unsigned short age) : age(age), isBlocked(false), posts(nullptr), countPost(0) {
    this->nickName = new char[strlen(nickname) + 1];
    strcpy(this->nickName, nickname);
}

User::~User() {

}
