//
// Created by yasen on 5/17/18.
//

#ifndef SOCIALNETWORK_MODERATOR_H
#define SOCIALNETWORK_MODERATOR_H


#include "User.h"

class Moderator : public User {
public:
    Moderator(const char* nickname, unsigned short age, unsigned long long id);


    void blockUser(User* user);
    void unblockUser(User* user);

    void blockModerator(Moderator* moderator);
    void unblockModerator(Moderator* moderator);

};


#endif //SOCIALNETWORK_MODERATOR_H
