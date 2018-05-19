//
// Created by yasen on 5/17/18.
//

#include <string.h>
#include <stdexcept>
#include "Admin.h"


Admin::Admin(const char* nickname, unsigned short age) : Moderator(nickname, age, 0) { } // admin id = 0

void Admin::addUser(User* user, User**& users, size_t& countUsers) {

    User** newUsers = new User* [countUsers + 1];

    for (int i = 0; i < countUsers; i++)
        newUsers[i] = users[i];

    newUsers[countUsers] = user;

    countUsers++;

    delete [] users;

    users = newUsers;
}

void Admin::removeUser(User* user, User**& users, size_t& countUsers) {

    for (int i = 0; i < countUsers; ++i) {
        if(users[i]->id == user->id) {
            std::swap(users[i], users[countUsers - 1]);
            break;
        }
    }

    delete users[countUsers - 1];
    --countUsers;
}

void Admin::addModerator(Moderator *moderator, Moderator **&moderators, size_t &countModerators) {

    Moderator** newModerators = new Moderator*[countModerators + 1];

    for (int i = 0; i < countModerators; i++)
        newModerators[i] = moderators[i];

    newModerators[countModerators] = moderator;

    countModerators++;

    delete [] moderators;

    moderators = newModerators;
}

void Admin::removeModerator(Moderator *moderator, Moderator **&moderators, size_t &countModerators) {

    for (int i = 0; i < countModerators; ++i) {
        if(moderators[i]->id == moderator->id) {
            std::swap(moderators[i], moderators[countModerators - 1]);
            break;
        }
    }

    delete moderators[countModerators - 1];
    --countModerators;
}

