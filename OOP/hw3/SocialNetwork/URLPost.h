//
// Created by yasen on 5/17/18.
//

#ifndef SOCIALNETWORK_URLPOST_H
#define SOCIALNETWORK_URLPOST_H


#include "Post.h"

class URLPost : public Post {
public:
    URLPost(const char* content, unsigned long long id, unsigned long long authorId);
    virtual Post* clone();

};


#endif //SOCIALNETWORK_URLPOST_H
