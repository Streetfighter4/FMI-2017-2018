//
// Created by yasen on 5/17/18.
//

#ifndef SOCIALNETWORK_SOCIALNETWORK_H
#define SOCIALNETWORK_SOCIALNETWORK_H

#include <iostream>
#include "User.h"
#include "Moderator.h"
#include "Admin.h"

class SocialNetwork {
    User** users;
    size_t countUsers;
    Moderator** moderators;
    size_t countModerators;
    Admin admin;

public:

    SocialNetwork();
    SocialNetwork(const SocialNetwork&) = delete;
    SocialNetwork& operator=(const SocialNetwork&) = delete;
    ~SocialNetwork();

    void info();

    void addUser(User* user);
    void addModerator(Moderator* moderator);
private:
    void clear();

};


#endif //SOCIALNETWORK_SOCIALNETWORK_H
