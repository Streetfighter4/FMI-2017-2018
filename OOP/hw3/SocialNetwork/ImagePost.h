//
// Created by yasen on 5/17/18.
//

#ifndef SOCIALNETWORK_IMAGEPOST_H
#define SOCIALNETWORK_IMAGEPOST_H


#include "Post.h"

class ImagePost : public Post {
public:
    ImagePost(const char* content, unsigned long long id, unsigned long long authorId);
    virtual Post* clone();
    virtual void parseToHTML(std::ofstream&);
};


#endif //SOCIALNETWORK_IMAGEPOST_H
