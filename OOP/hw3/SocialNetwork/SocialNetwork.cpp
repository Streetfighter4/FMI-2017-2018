//
// Created by yasen on 5/17/18.
//

#include "SocialNetwork.h"

SocialNetwork::SocialNetwork() : users(nullptr), countUsers(0), moderators(nullptr), countModerators(0) , admin("Admin", 0) {
}

SocialNetwork::~SocialNetwork() {
    clear();
}

void SocialNetwork::clear() {
    for (int i = 0; i < countUsers; ++i) {
        delete users[i];
    }
    delete[] users;
    users = nullptr;
    countUsers = 0;

    for (int i = 0; i < countModerators; ++i) {
        delete moderators[i];
    }
    delete[] moderators;
    moderators = nullptr;
    countModerators = 0;

}

void SocialNetwork::addUser(User* user) {
    admin.addUser(user, users, countUsers);
}

void SocialNetwork::addModerator(Moderator* moderator) {
    admin.addModerator(moderator, moderators, countModerators);
}

void SocialNetwork::info() {
    std::cout << "There are " << countUsers << " users:" << std::endl;
}




