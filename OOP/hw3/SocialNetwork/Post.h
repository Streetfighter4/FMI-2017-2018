//
// Created by yasen on 5/17/18.
//

#ifndef SOCIALNETWORK_POST_H
#define SOCIALNETWORK_POST_H

#include <fstream>

class Post {


private:
    char* content;
    unsigned long long id;
    unsigned long long authorId;

public:

    Post(const char* content, unsigned long long id, unsigned long long authorId);
    virtual ~Post();

public:
    const char* getContent();
    unsigned long long getId();
    unsigned long long getAuthorId();
    virtual Post* clone() = 0;
    virtual void parseToHTML(std::ofstream&) = 0;
};


#endif //SOCIALNETWORK_POST_H
