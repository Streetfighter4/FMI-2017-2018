//
// Created by yasen on 5/17/18.
//

#include "Moderator.h"

Moderator::Moderator(const char* nickname, unsigned short age, unsigned long long id) : User(nickname, age, id) { }

void Moderator::blockUser(User* user) {
    user->setIsBloked(true);
}

void Moderator::unblockUser(User* user) {
    user->setIsBloked(false);
}

void Moderator::blockModerator(Moderator* moderator) {
    moderator->setIsBloked(true);
}

void Moderator::unblockModerator(Moderator* moderator) {
    moderator->setIsBloked(false);
}
