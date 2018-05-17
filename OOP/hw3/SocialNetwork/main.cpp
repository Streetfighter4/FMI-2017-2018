#include <iostream>
#include <string.h>
#include <stdexcept>
#include "User.h"
#include "Moderator.h"
#include "Admin.h"
#include "SocialNetwork.h"

User* createUser(const char* str, const char* name, const unsigned short age) {

    if (str == nullptr)
        return nullptr;

    if (strcmp(str, "add_moderator") == 0)
        return new Moderator(name, age);

    if (strcmp(str, "add_user") == 0)
        return new User(name, age);

    return nullptr;
}

int main() {
    SocialNetwork sn;

    try {
        sn.addUser(createUser("add_user", "Yasen", 20));
    } catch (std::invalid_argument&) {

        std::cerr << "invalid input, user not added!\n";
    }
    sn.info();
    return 0;
}