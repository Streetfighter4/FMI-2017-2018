//
// Created by yasen on 5/17/18.
//

#ifndef SOCIALNETWORK_ADMIN_H
#define SOCIALNETWORK_ADMIN_H


#include "Moderator.h"

class Admin: public Moderator {


public:
    Admin() = delete;
    Admin(const char* nickname, unsigned short age);

    void addUser(User* user, User**& users, size_t& countUsers);
    void removeUser(User*);

    void addModerator(Moderator* moderator, Moderator**& moderators, size_t& countModerators);
    void removeModerator(Moderator* moderator);
};


#endif //SOCIALNETWORK_ADMIN_H
