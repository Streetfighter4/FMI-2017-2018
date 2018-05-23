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

    unsigned long long getLargestIdOfUser();
    unsigned long long getLargestIdOfPost();
    User* findUser(const char* nickname, bool& type);
    void info();

    void addUser(User* user);
    void removeUser(User* user);

    void addModerator(Moderator* moderator);
    void removeModerator(Moderator* moderator);

    void blockUser(User* user, bool type);
    void unblockUser(User* user, bool type);

    void createPost(Post* post, bool typeUser);
    void deletePost(unsigned long long id);

    void viewPostById(unsigned long long id);
    void viewPostByNickName(const char* nickName);
private:

    bool nickNameExist(const char* nickname);
    void clear();

};


#endif //SOCIALNETWORK_SOCIALNETWORK_H
