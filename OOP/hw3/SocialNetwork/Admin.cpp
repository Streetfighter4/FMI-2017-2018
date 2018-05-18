//
// Created by yasen on 5/17/18.
//

#include <string.h>
#include <stdexcept>
#include "Admin.h"


Admin::Admin(const char* nickname, unsigned short age) : Moderator(nickname, age, 0) { }

void Admin::addUser(User* user, User**& users, size_t& countUsers) {
    if (user == nullptr)
        throw std::invalid_argument("null pointer passed");


    //memory for + one base pointer
    User** newUsers = new User* [countUsers + 1];

    //using the old pointers
    for (int i = 0; i < countUsers; i++)
        newUsers[i] = users[i];

    newUsers[countUsers] = user;

    countUsers++;

    //cleaning only the array of pointers
    //not the pointers themselves
    delete [] users;

    users = newUsers;
}

void Admin::removeUser(User* user, User**& users, size_t& countUsers) {
    if (user == nullptr)
        throw std::invalid_argument("null pointer passed");

    std::cout << "Admin removeUser" << std::endl;
    for (int i = 0; i < countUsers; ++i) {
        if(users[i]->id == user->id) {
            users[i] = users[countUsers - 1];
            std::cout << "find Ali!" << std::endl;
            break;
        }
    }

    std::cout << "users[0] must be Miro.id: " << users[0]->id << std::endl;
    std::cout << "users[2] must be nobody: " << users[2]->id << std::endl;
    delete users[countUsers - 1];
    //TODO: Better remove
    --countUsers;
}

void Admin::addModerator(Moderator *moderator, Moderator **&moderators, size_t &countModerators) {
    if (moderator == nullptr)
        throw std::invalid_argument("null pointer passed");


    //memory for + one base pointer
    Moderator** newModerators = new Moderator*[countModerators + 1];
    //using the old pointers
    for (int i = 0; i < countModerators; i++)
        newModerators[i] = moderators[i];

    newModerators[countModerators] = moderator;

    countModerators++;

    //cleaning only the array of pointers
    //not the pointers themselves
    delete [] moderators;

    moderators = newModerators;

}

