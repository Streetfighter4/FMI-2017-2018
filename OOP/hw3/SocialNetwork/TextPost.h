//
// Created by yasen on 5/17/18.
//

#ifndef SOCIALNETWORK_TEXTPOST_H
#define SOCIALNETWORK_TEXTPOST_H


#include "Post.h"

class TextPost : public Post {
public:
    TextPost(const char* content, unsigned long long id, unsigned long long authorId);
    virtual Post* clone();
    virtual void parseToHTML(std::ofstream&);
};


#endif //SOCIALNETWORK_TEXTPOST_H
