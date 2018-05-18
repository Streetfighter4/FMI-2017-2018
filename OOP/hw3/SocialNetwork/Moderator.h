//
// Created by yasen on 5/17/18.
//

#ifndef SOCIALNETWORK_MODERATOR_H
#define SOCIALNETWORK_MODERATOR_H


#include "User.h"

class Moderator : public User {
public:
    Moderator(const char* nickname, unsigned short age, unsigned long long id);


    void blockUser(User*);
    void unblockUser(User*);

};


#endif //SOCIALNETWORK_MODERATOR_H
