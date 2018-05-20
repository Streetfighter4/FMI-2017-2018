//
// Created by yasen on 5/17/18.
//

#include "TextPost.h"

TextPost::TextPost(const char *content, unsigned long long id, unsigned long long authorId) : Post(content, -1, id, authorId) { }

Post* TextPost::clone() {
    return new TextPost(*this);
}

