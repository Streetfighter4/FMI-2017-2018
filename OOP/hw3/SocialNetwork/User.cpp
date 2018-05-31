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
        clear();
        id = other.id;
        age = other.age;
        isBlocked = other.isBlocked;

        nickName = new char[strlen(other.nickName) + 1];
        strcpy(nickName, other.nickName);

        posts = new Post* [other.countPost]; // allocating memory for all base pointers

        for (int i = 0; i < other.countPost; i++)
            posts[i] = other.posts[i]->clone();

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

void User::changeNickName(const char* newNickName) {
    delete[] nickName;
    this->nickName = new char[strlen(newNickName) + 1];
    strcpy(nickName, newNickName);
}

void User::addPost(Post *post) {
    Post** newPosts = new Post*[countPost+1];
    for (int i = 0; i < countPost; ++i) {
        newPosts[i] = posts[i]->clone();
    }
    delete[] posts;
    newPosts[countPost] = post;
    posts = newPosts;
    ++countPost;
}

void User::deletePost(unsigned long long id) {
    for (int i = 0; i < countPost; ++i) {
        if(posts[i]->getId() == id) {
            std::swap(posts[i], posts[countPost-1]);
            break;
        }
    }

    delete posts[countPost - 1];
    --countPost;
}

void User::personalInfo() {
     std::cout << "Name: " << nickName << ", " << "Age: "<< age << ",id: " << id
                << ", Blocked: " << isBlocked << ", CountPosts: " << countPost << std::endl;
}

unsigned long long User::getId() const {
    return id;
}

char* User::getNickName() const {
    return nickName;
}

unsigned short User::getAge() const {
    return age;
}

bool User::getIsBloked() const {
    return isBlocked;
}

void User::setIsBloked(bool isBloked) {
    this->isBlocked = isBloked;
}

size_t User::getCountPost() const {
    return countPost;
}
