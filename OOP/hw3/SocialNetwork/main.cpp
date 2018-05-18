#include <iostream>
#include <string.h>
#include <stdexcept>
#include "User.h"
#include "Moderator.h"
#include "Admin.h"
#include "SocialNetwork.h"

Moderator* createModerator(const char* name, const unsigned short age, unsigned long long id) {
    return new Moderator(name, age, id);
}

User* createUser(const char* name, const unsigned short age, unsigned long long id) {
    return new User(name, age, id);
}

int main() {
    SocialNetwork sn;

    try {
        sn.addModerator(createModerator("Yasen", 20, sn.getLargestId() + 1));
        sn.addModerator(createModerator("Toni", 20, sn.getLargestId() + 1));
        sn.addModerator(createModerator("Niki", 19, sn.getLargestId() + 1));
    } catch (std::invalid_argument&) {
        std::cerr << "invalid input, user not added!\n";
    }

    try {
        sn.addUser(createUser("Ali", 19, sn.getLargestId() + 1));
        sn.addUser(createUser("Viktor", 19, sn.getLargestId() + 1));
        sn.addUser(createUser("Miro", 22, sn.getLargestId() + 1));

    } catch (std::invalid_argument&) {
        std::cerr << "invalid input, user not added!\n";
    }

    sn.info();
    try {
        User* ali = sn.findUser("Ali");
        std::cout << "Ali id: " << ali->id << std::endl;
        sn.removeUser(ali);
    } catch (std::invalid_argument&) {
        std::cerr << "invalid input, user not removed!\n";
    }


    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;


    sn.info();

    return 0;
}