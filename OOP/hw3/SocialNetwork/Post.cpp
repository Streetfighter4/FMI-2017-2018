//
// Created by yasen on 5/17/18.
//

#include <cstring>
#include "Post.h"

Post::Post(const char* newContent, unsigned long long id, unsigned long long authorId) : id(id), authorId(authorId) {
    content = new char[strlen(newContent) + 1];
    strcpy(content, newContent);
}

Post::~Post() {
    delete[] content;
}

const char* Post::getContent() {
    return content;
}
unsigned long long int Post::getId() {
    return id;
}

unsigned long long Post::getAuthorId() {
    return authorId;
}
