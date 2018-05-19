//
// Created by yasen on 5/17/18.
//

#include "Moderator.h"

Moderator::Moderator(const char* nickname, unsigned short age, unsigned long long id) : User(nickname, age, id){

}

void Moderator::blockUser(User* user) {
    user->isBlocked = true;
}

void Moderator::unblockUser(User* user) {
    user->isBlocked = false;
}

void Moderator::blockModerator(Moderator* moderator) {
    moderator->isBlocked = true;
}

void Moderator::unblockModerator(Moderator* moderator) {
    moderator->isBlocked = false;
}
