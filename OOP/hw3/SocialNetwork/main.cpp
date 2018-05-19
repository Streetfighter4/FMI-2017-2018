#include <iostream>
#include <stdexcept>
#include "User.h"
#include "Moderator.h"
#include "SocialNetwork.h"
#include <typeinfo>

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
        sn.addUser(createUser("Miro", 19, sn.getLargestId() + 1));
    } catch (std::invalid_argument&) {
        std::cerr << "invalid input, user not added!\n";
    }

    sn.info();
    try {
        bool type = false;
        User* user = sn.findUser("Miro", type);
        //TODO: think better way to find is a user or moderator
        if(type) {
            std::cout << "Find moderator" << std::endl;
            sn.removeModerator(static_cast<Moderator*>(user));
        } else {
            std::cout << "Find user" << std::endl;
            sn.removeUser(user);
        }
    } catch (std::invalid_argument&) {
        std::cerr << "invalid input, user not removed!\n";
    }


    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;


    sn.info();

    try{
        bool type = false;
        User* user = sn.findUser("Viktor", type);
        user->changeNickName("FitnesBatka");
    } catch (std::invalid_argument&) {
        std::cerr << "invalid input, user not rename!\n";
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;


    sn.info();

    try{
        bool type = false;
        User* user = sn.findUser("Ali", type);
        sn.blockUser(user, type);
    } catch (std::invalid_argument&) {
        std::cerr << "invalid input, user not rename!\n";
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;


    sn.info();

    try{
        bool type = false;
        User* user = sn.findUser("Ali", type);
        sn.unblockUser(user, type);
    } catch (std::invalid_argument&) {
        std::cerr << "invalid input, user not rename!\n";
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;


    sn.info();


    return 0;
}