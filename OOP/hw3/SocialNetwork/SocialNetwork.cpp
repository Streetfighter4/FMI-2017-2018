//
// Created by yasen on 5/17/18.
//

#include <cstring>
#include <stdexcept>
#include "SocialNetwork.h"
#include <climits>

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
    else if(nickNameExist(user->getNickName()))
        throw std::invalid_argument("nickname exist in system");

    admin.addUser(user, users, countUsers);
}

void SocialNetwork::removeUser(User* user) {

    if (user == nullptr) {
        throw std::invalid_argument("null pointer passed");
    } else if(!nickNameExist(user->getNickName())){
        throw std::invalid_argument("nickname exist in system");
    }

    admin.removeUser(user, users, countUsers);
}

void SocialNetwork::addModerator(Moderator* moderator) {
    if (moderator == nullptr)
        throw std::invalid_argument("null pointer passed");
    else if(nickNameExist(moderator->getNickName()))
        throw std::invalid_argument("nickname exist is system");

    admin.addModerator(moderator, moderators, countModerators);
}

void SocialNetwork::removeModerator(Moderator* moderator) {
    if (moderator == nullptr)
        throw std::invalid_argument("null pointer passed");
    else if(!nickNameExist(moderator->getNickName()))
        throw std::invalid_argument("nickname does not exist in system");

    admin.removeModerator(moderator, moderators, countModerators);
}

void SocialNetwork::info() {
    std::cout << "There are " << countUsers << " users and " << countModerators << " moderators" << std::endl;

    unsigned short oldest = 0;
    unsigned long long idOfOldestUser = 0;
    unsigned short youngest = USHRT_MAX;
    unsigned long long idOfYoungestUser = 0;

    std::cout << "Users: " << std::endl;
    for (int i = 0; i < countUsers; ++i) {
        users[i]->personalInfo();
        if(users[i]->getAge() > oldest) {
            oldest = users[i]->getAge();
            idOfOldestUser = users[i]->getId();
        }
        if(users[i]->getAge() < youngest) {
            youngest = users[i]->getAge();
            idOfYoungestUser = users[i]->getId();
        }
    }

    std::cout << "Moderators: " << std::endl;

    for (int i = 0; i < countModerators; ++i) {
        moderators[i]->personalInfo();
        if(moderators[i]->getAge() > oldest){
            oldest = moderators[i]->getAge();
            idOfOldestUser = moderators[i]->getId();
        }
        if(moderators[i]->getAge() < youngest) {
            youngest = moderators[i]->getAge();
            idOfYoungestUser = moderators[i]->getId();
        }
    }

    std::cout << "Admin: " << std::endl;
    admin.personalInfo();

    User* oldestUser = getUserById(idOfOldestUser);
    User* youngestUser = getUserById(idOfYoungestUser);

    std::cout << "Oldest user: " << oldestUser->getNickName() << " , Age: " << oldestUser->getAge() << std::endl;
    std::cout << "Youngest user: " << youngestUser->getNickName() << " , Age: " << youngestUser->getAge() << std::endl;
}

unsigned long long SocialNetwork::getLargestIdOfUser() {
    if(countUsers == 0 && countModerators == 0)
        return 0;

    unsigned long long id = 0;

    for (int i = 0; i < countUsers; ++i) {
        if(users[i]->getId() > id)
            id = users[i]->getId();
    }

    for (int i = 0; i < countModerators; ++i) {
        if(moderators[i]->getId() > id)
            id = moderators[i]->getId();
    }

    return id;
}

unsigned long long SocialNetwork::getLargestIdOfPost() {
    unsigned long long id = 0;

    for (int i = 0; i < countUsers; ++i) {
        for (int j = 0; j < users[i]->getCountPost(); ++j) {
            if(users[i]->posts[j]->getId() > id)
                id = users[i]->posts[j]->getId();
        }
    }

    for (int i = 0; i < countModerators; ++i) {
        for (int j = 0; j < moderators[i]->getCountPost(); ++j) {
            if(moderators[i]->posts[j]->getId() > id)
                id = moderators[i]->posts[j]->getId();
        }
    }

    for (int k = 0; k < admin.getCountPost(); ++k) {
        if(admin.posts[k]->getId() > id)
            id = admin.posts[k]->getId();
    }
    return id;
}

User* SocialNetwork::findUser(const char *nickname, int& type) {
    if(nickname == nullptr)
        throw std::invalid_argument("null pointer passed");
    if(!nickNameExist(nickname))
        throw std::invalid_argument("nickname does not exist in system");

    for (int i = 0; i < countUsers; ++i) {
        if(strcmp(nickname, users[i]->getNickName()) == 0) {
            type = 1;
            return users[i];
        }
    }

    for (int i = 0; i < countModerators; ++i) {
        if(strcmp(nickname, moderators[i]->getNickName()) == 0) {
            type = -1;
            return moderators[i];
        }
    }

    if(strcmp(nickname, admin.getNickName()) == 0) {
        type = 0;
        return &admin;
    }

    return nullptr;
}

bool SocialNetwork::nickNameExist(const char* nickname) {

    for (int i = 0; i < countUsers; ++i) {
        if(strcmp(users[i]->getNickName(), nickname) == 0) {
            return true;
        }
    }

    for (int i = 0; i < countModerators; ++i) {
        if(strcmp(moderators[i]->getNickName(), nickname) == 0) {
            return true;
        }
    }

    return strcmp(nickname, admin.getNickName()) == 0;
}

void SocialNetwork::blockUser(User* user, int typeUser) {
    if(typeUser == -1) {
        admin.blockModerator(static_cast<Moderator*>(user));
    } else if(typeUser == 1) {
        admin.blockUser(user);
    }
}

void SocialNetwork::unblockUser(User* user, int typeUser) {
    if(typeUser == -1) {
        admin.unblockModerator(static_cast<Moderator*>(user));
    } else if (typeUser == 1) {
        admin.unblockUser(user);
    }
}

void SocialNetwork::createPost(Post* post, int typeUser) {
    if(typeUser == -1) {
        for (int i = 0; i < countModerators; ++i) {
            if (moderators[i]->getId() == post->getAuthorId()) {
                moderators[i]->addPost(post);
                return;
            }
        }
    } else if (typeUser == 1){
         for (int i = 0; i < countUsers; ++i) {
            if (users[i]->getId() == post->getAuthorId()) {
                users[i]->addPost(post);
                return;
            }
        }
    } else if (typeUser == 0) {
        admin.addPost(post);
        return;
    }
}

void SocialNetwork::deletePost(unsigned long long id) {
    for (int i = 0; i < countUsers; ++i) {
        for (int j = 0; j < users[i]->getCountPost(); ++j) {
            if(users[i]->posts[j]->getId() == id)
                users[i]->deletePost(id);
        }
    }

    for (int i = 0; i < countModerators; ++i) {
        for (int j = 0; j < moderators[i]->getCountPost(); ++j) {
            if(moderators[i]->posts[j]->getId() == id)
                moderators[i]->deletePost(id);
        }
    }

    for (int k = 0; k < admin.getCountPost(); ++k) {
        if(admin.posts[k]->getId() == id)
            admin.deletePost(id);
    }
}

void SocialNetwork::viewPostById(unsigned long long id) {
    if(!postExist(id)) {
        throw std::out_of_range("Not such post with this id");
    }
    std::string str = std::to_string(id);
    std::ofstream ofile("post_" + str + ".html");

    const char* str1 = "<!DOCTYPE html>\n<html>\n<body>\n\n";
    const char* str2 = "\n\n</body>\n</html>";

    ofile << str1;

    for (int i = 0; i < countUsers; ++i) {
        for (int j = 0; j < users[i]->getCountPost(); ++j) {
            if(users[i]->posts[j]->getId() == id)
                users[i]->posts[j]->parseToHTML(ofile);
        }
    }

    for (int i = 0; i < countModerators; ++i) {
        for (int j = 0; j < moderators[i]->getCountPost(); ++j) {
            if(moderators[i]->posts[j]->getId() == id)
                users[i]->posts[j]->parseToHTML(ofile);
        }
    }

    for (int k = 0; k < admin.getCountPost(); ++k) {
        if(admin.posts[k]->getId() == id)
            admin.posts[k]->parseToHTML(ofile);
    }
    ofile << str2;
    ofile.close();
}

void SocialNetwork::viewPostByNickName(const char *nickName) {
    int typeUser;
    User* user = findUser(nickName, typeUser);

    char* fileName = new char[strlen(user->getNickName())+12];
    strcpy(fileName, user->getNickName());
    strcat(fileName, "_posts.html");

    std::ofstream ofile;
    const char* str1 = "<!DOCTYPE html>\n<html>\n<body>\n\n";
    const char* str2 = "\n\n</body>\n</html>";
    ofile.open(fileName); //for clear old content if file already exist
    ofile.close();
    ofile.open(fileName, std::ios::app);
    ofile << str1;
    for (int i = 0; i < (user->getCountPost()); ++i) {
        user->posts[i]->parseToHTML(ofile);
    }

    ofile << str2;
    ofile.close();

    delete[] fileName;
}

Admin* SocialNetwork::getAdmin() {
    return &admin;
}

bool SocialNetwork::postExist(unsigned long long id) {

    for (int i = 0; i < countUsers; ++i) {
        for (int j = 0; j < users[i]->getCountPost(); ++j) {
            if (users[i]->posts[j]->getId() == id)
                return true;
        }
    }

    for (int i = 0; i < countModerators; ++i) {
        for (int j = 0; j < moderators[i]->getCountPost(); ++j) {
            if (moderators[i]->posts[j]->getId() == id)
                return true;
        }
    }

    for (int k = 0; k < admin.getCountPost(); ++k) {
        if(admin.posts[k]->getId() == id)
            return true;
    }

    return false;
}

User* SocialNetwork::getUserById(unsigned long long id) {
    for (int i = 0; i < countUsers; ++i) {
        if(users[i]->getId() == id)
            return users[i];
    }

    for (int j = 0; j < countModerators; ++j) {
        if(moderators[j]->getId() == id)
            return moderators[j];
    }

    if(admin.getId() == id)
        return &admin;

    return nullptr;
}



