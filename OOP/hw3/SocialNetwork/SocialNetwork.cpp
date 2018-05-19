//
// Created by yasen on 5/17/18.
//

#include <cstring>
#include <stdexcept>
#include "SocialNetwork.h"
#include "User.h"

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
    if (user == nullptr)
        throw std::invalid_argument("null pointer passed");
    else if(nickNameExist(user->nickName))
        throw std::invalid_argument("nickname exist in system");

    admin.addUser(user, users, countUsers);
}

void SocialNetwork::removeUser(User* user) {

    if (user == nullptr) {
        throw std::invalid_argument("null pointer passed");
    } else if(!nickNameExist(user->nickName)){
        throw std::invalid_argument("nickname exist in system");
    }

    admin.removeUser(user, users, countUsers);
}

void SocialNetwork::addModerator(Moderator* moderator) {
    if (moderator == nullptr)
        throw std::invalid_argument("null pointer passed");
    else if(nickNameExist(moderator->nickName))
        throw std::invalid_argument("nickname exist is system");

    admin.addModerator(moderator, moderators, countModerators);
}

void SocialNetwork::removeModerator(Moderator* moderator) {
    if (moderator == nullptr)
        throw std::invalid_argument("null pointer passed");
    else if(!nickNameExist(moderator->nickName))
        throw std::invalid_argument("nickname does not exist in system");

    admin.removeModerator(moderator, moderators, countModerators);
}

void SocialNetwork::info() {
    std::cout << "There are " << countUsers << " users and " << countModerators << " moderators" << std::endl;

    std::cout << "Users: " << std::endl;
    for (int i = 0; i < countUsers; ++i) {
        std::cout << "Name: " << users[i]->nickName << ", " << users[i]->age << ",id: " << users[i]->id
                << "Blocked: " << users[i]->isBlocked << std::endl;
    }

    std::cout << "Moderators: " << std::endl;

    for (int i = 0; i < countModerators; ++i) {
        std::cout << "Name: " << moderators[i]->nickName << ", " << moderators[i]->age << ", id: " << moderators[i]->id
                    << "Blocked: " << moderators[i]->isBlocked << std::endl;
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

User* SocialNetwork::findUser(const char *nickname, bool& type) {
    if(nickname == nullptr)
        throw std::invalid_argument("null pointer passed");
    if(!nickNameExist(nickname))
        throw std::invalid_argument("nickname does not exist in system");

    for (int i = 0; i < countUsers; ++i) {
        if(strcmp(nickname, users[i]->nickName) == 0) {
            type = false;
            return users[i];
        }
    }

    for (int i = 0; i < countModerators; ++i) {
        if(strcmp(nickname, moderators[i]->nickName) == 0) {
            type = true;
            return moderators[i];
        }
    }
    return nullptr;
}

bool SocialNetwork::nickNameExist(const char* nickname) {

    for (int i = 0; i < countUsers; ++i) {
        if(strcmp(users[i]->nickName, nickname) == 0) {
            return true;
        }
    }

    for (int i = 0; i < countModerators; ++i) {
        if(strcmp(moderators[i]->nickName, nickname) == 0) {
            return true;
        }
    }

    return false;
}

void SocialNetwork::blockUser(User* user, bool type) {
    if(type) {
        admin.blockModerator(static_cast<Moderator*>(user));
    } else {
        admin.blockUser(user);
    }
}

void SocialNetwork::unblockUser(User* user, bool type) {
    if(type) {
        admin.unblockModerator(static_cast<Moderator*>(user));
    } else {
        admin.unblockUser(user);
    }
}




