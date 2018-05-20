//
// Created by yasen on 5/17/18.
//

#include "URLPost.h"

URLPost::URLPost(const char *content, unsigned long long id, unsigned long long authorId) : Post(content, 0, id, authorId) { }

Post *URLPost::clone() {
    return new URLPost(*this);
}
