//
// Created by yasen on 5/17/18.
//

#include <cstring>
#include <stdexcept>
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

void SocialNetwork::removeUser(User *user) {
    std::cout << "SocialNetwork removeUser" << std::endl;
    admin.removeUser(user, users, countUsers);
}

void SocialNetwork::addModerator(Moderator* moderator) {
    admin.addModerator(moderator, moderators, countModerators);
}

void SocialNetwork::info() {
    std::cout << "There are " << countUsers << " users and " << countModerators << " moderators" << std::endl;

    std::cout << "Users: " << std::endl;
    for (int i = 0; i < countUsers; ++i) {
        std::cout << "Name: " << users[i]->nickName << ", " << users[i]->age << ",id: " << users[i]->id << std::endl;
    }

    std::cout << "Moderators: " << std::endl;

    for (int i = 0; i < countModerators; ++i) {
        std::cout << "Name: " << moderators[i]->nickName << ", " << moderators[i]->age << ", id: " << moderators[i]->id << std::endl;
    }

}

unsigned long long SocialNetwork::getLargestId() {
    if(countUsers == 0 && countModerators == 0)
        return 0;

    unsigned long long id = 0;

    for (int i = 0; i < countUsers; ++i) {
        if(users[i]->id > id)
            id = users[i]->id;
    }

    for (int i = 0; i < countModerators; ++i) {
        if(moderators[i]->id > id)
            id = moderators[i]->id;
    }

    return id;
}

User* SocialNetwork::findUser(const char *nickname) {
    if(nickname == nullptr)
        throw std::invalid_argument("null pointer passed");

    for (int i = 0; i < countUsers; ++i) {
        if(strcmp(nickname, users[i]->nickName) == 0) {
            return users[i];
        }
    }
}




