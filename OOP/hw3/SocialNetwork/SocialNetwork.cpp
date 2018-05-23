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
        users[i]->personalInfo();
    }

    std::cout << "Moderators: " << std::endl;

    for (int i = 0; i < countModerators; ++i) {
        moderators[i]->personalInfo();
    }

    std::cout << "Admin: " << std::endl;
    admin.personalInfo();
}

unsigned long long SocialNetwork::getLargestIdOfUser() {
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

unsigned long long SocialNetwork::getLargestIdOfPost() {
    unsigned long long id = 0;

    for (int i = 0; i < countUsers; ++i) {
        for (int j = 0; j < users[i]->countPost; ++j) {
            if(users[i]->posts[j]->getId() > id)
                id = users[i]->posts[j]->getId();
        }
    }

    for (int i = 0; i < countModerators; ++i) {
        for (int j = 0; j < moderators[i]->countPost; ++j) {
            if(moderators[i]->posts[j]->getId() > id)
                id = moderators[i]->posts[j]->getId();
        }
    }

    for (int k = 0; k < admin.countPost; ++k) {
        if(admin.posts[k]->getId() > id)
            id = admin.posts[k]->getId();
    }
    std::cout << "largest id: " << id << std::endl;
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

void SocialNetwork::createPost(Post* post, bool typeUser) {
    if(typeUser) {
        for (int i = 0; i < countModerators; ++i) {
            if (moderators[i]->id == post->getAuthorId()) {
                moderators[i]->addPost(post);
            }
        }
    } else {
         for (int i = 0; i < countUsers; ++i) {
            if (users[i]->id == post->getAuthorId()) {
                users[i]->addPost(post);
            }
        }
    }
}

void SocialNetwork::deletePost(unsigned long long id) {
    for (int i = 0; i < countUsers; ++i) {
        for (int j = 0; j < users[i]->countPost; ++j) {
            if(users[i]->posts[j]->getId() == id)
                users[i]->deletePost(id);
        }
    }

    for (int i = 0; i < countModerators; ++i) {
        for (int j = 0; j < moderators[i]->countPost; ++j) {
            if(moderators[i]->posts[j]->getId() == id)
                moderators[i]->deletePost(id);
        }
    }

    for (int k = 0; k < admin.countPost; ++k) {
        if(admin.posts[k]->getId() == id)
            admin.deletePost(id);
    }
}

void SocialNetwork::viewPostById(unsigned long long id) {
    std::ofstream ofile("name1.html");

    for (int i = 0; i < countUsers; ++i) {
        for (int j = 0; j < users[i]->countPost; ++j) {
            if(users[i]->posts[j]->getId() == id)
                users[i]->posts[j]->parseToHTML(ofile);
        }
    }

    for (int i = 0; i < countModerators; ++i) {
        for (int j = 0; j < moderators[i]->countPost; ++j) {
            if(moderators[i]->posts[j]->getId() == id)
                users[i]->posts[j]->parseToHTML(ofile);
        }
    }

    for (int k = 0; k < admin.countPost; ++k) {
        if(admin.posts[k]->getId() == id)
            admin.posts[k]->parseToHTML(ofile);
    }

}

void SocialNetwork::viewPostByNickName(const char *nickName) {
    bool typeUser = false;
    User* user = findUser(nickName, typeUser);
    std::cout << "ID: " << user->id << std::endl;

    char* fileName = new char[strlen(user->nickName)+12];
    strcpy(fileName, user->nickName);
    strcat(fileName, "_posts.html");

    std::ofstream ofile(fileName, std::ios::app);

    std::cout << fileName << std::endl;
    std::cout << user->countPost << std::endl;
    for (int i = 0; i < (user->countPost); ++i) {
        std::cout << "i: " << i << std::endl;
        user->posts[i]->parseToHTML(ofile);
    }
}



