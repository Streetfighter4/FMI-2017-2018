#include <iostream>
#include <stdexcept>
#include "User.h"
#include "Moderator.h"
#include "SocialNetwork.h"
#include "TextPost.h"
#include "URLPost.h"
#include "ImagePost.h"
#include <typeinfo>
#include <cstring>
#include <iomanip>

Moderator* createModerator(const char* name, const unsigned short age, unsigned long long id) {
    return new Moderator(name, age, id);
}

User* createUser(const char* name, const unsigned short age, unsigned long long id) {
    return new User(name, age, id);
}

Post* createPost(const char* content, int type, unsigned long long id, unsigned long long authorId) {
    if (content == nullptr)
        return nullptr;
    if (type == -1) {
        return new TextPost(content, id, authorId);
    }

    if (type == 0) {
        return new URLPost(content, id, authorId);
    }

    if (type == 1)
        return new ImagePost(content, id, authorId);

    return nullptr;
}

int main() {
    SocialNetwork sn;

    char actor[1024];
    char action[1024];
    char subject[1024];
    char typePost[8];
    unsigned short age;

    while(true) {
        std::cin >> actor;

        if(strcmp(actor, "info") == 0) {
            sn.info();
            continue;
        } else if(strcmp(actor, "exit") == 0) {
            break;
        }

        std::cin >> action;

        if(strcmp(action, "add_moderator") == 0) {
            std::cin >> subject;

            std::cin.ignore();
            std::cin >> age;

            std::cin.ignore();
            if(strcmp(actor, sn.getAdmin()->getNickName()) == 0) {
                try {
                    sn.addModerator(createModerator(subject, age, sn.getLargestIdOfUser() + 1));
                    std::cout << subject << " has been added" << std::endl;
                } catch (std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }
            } else {
                std::cout << "This user don't have rights for this action!" << std::endl;
            }
        } else if(strcmp(action, "add_user") == 0) {
            std::cin >> subject;
            std::cin >> age;
            std::cin.ignore();

            if(strcmp(actor, sn.getAdmin()->getNickName()) == 0) {
                try {
                    sn.addUser(createUser(subject, age, sn.getLargestIdOfUser() + 1));
                    std::cout << subject << " has been added" << std::endl;
                } catch (std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }
            } else {
                std::cout << "This user don't have rights for this action!" << std::endl;
            }
        } else if(strcmp(action, "remove_user") == 0) {
            std::cin >> subject;

            if(strcmp(actor, sn.getAdmin()->getNickName()) == 0) {
                try {
                    int type;
                    User* user = sn.findUser(subject, type);
                    if(type == -1) {
                        sn.removeModerator(static_cast<Moderator*>(user));
                        std::cout << subject << " has been removed" << std::endl;
                    } else if(type == 1){
                        sn.removeUser(user);
                        std::cout << subject << " has been removed" << std::endl;
                    } else if(type == 0) {
                        std::cerr << "Administrator can't remove!\n";
                    }
                } catch (std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }
            } else {
                std::cout << "This user don't have rights for this action!" << std::endl;
            }
        } else if(strcmp(action, "rename") == 0) {
            std::cin >> subject;
            if(!sn.nickNameExist(subject)) {
                try {
                    int typeUser;
                    User *user = sn.findUser(actor, typeUser);
                    user->changeNickName(subject);
                    std::cout << "User " << actor << " is now known as " << subject << std::endl;
                } catch (std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }
            } else {
                std::cout << "This username already exist!" << std::endl;
            }
        } else if(strcmp(action, "block") == 0) {
            std::cin >> subject;
            try{
                int typeUser;
                User* user = sn.findUser(actor, typeUser);
                if((typeUser == 0 || typeUser == -1) && !user->getIsBloked()) {
                    user = sn.findUser(subject, typeUser);
                    if(typeUser != 0) {
                        sn.blockUser(user, typeUser);
                        std::cout << subject << " has been blocked" << std::endl;
                    } else {
                        std::cout << "You can't block/unblock this user! This is Admin\n" << std::endl;
                    }
                } else {
                    std::cout << "This user don't have rights for this action!" << std::endl;
                }
            } catch (std::exception& e) {
                std::cerr << e.what() << std::endl;
            }

        } else if(strcmp(action, "unblock") == 0) {
            std::cin >> subject;
            try{
                int typeUser;
                User* user = sn.findUser(actor, typeUser);
                if((typeUser == 0 || typeUser == -1) && !user->getIsBloked()) {
                    user = sn.findUser(subject, typeUser);
                    if(typeUser != 0) {
                        sn.unblockUser(user, typeUser);
                        std::cout << subject << " has been unblocked" << std::endl;
                    } else {
                        std::cout << "You can't block/unblock this user! This is Admin\n" << std::endl;
                    }
                } else {
                    std::cout << "This user don't have rights for this action!" << std::endl;
                }
            } catch (std::exception& e) {
                std::cerr << e.what() << std::endl;
            }

        } else if (strcmp(action, "post") == 0) {
            try {
                int typeUser;
                User* author = sn.findUser(actor, typeUser);
                if (!author->getIsBloked()) {
                    std::cin >> typePost;

                    if (strcmp(typePost, "[text]") == 0) {
                        std::cin.getline(subject, 1024);
                        unsigned long long id = sn.getLargestIdOfPost() +1;
                        Post *post = createPost(subject, -1, id, author->getId());
                        sn.createPost(post, typeUser);
                        std::cout << "Post " << id << " has been created" << std::endl;

                    } else if (strcmp(typePost, "[url]") == 0) {
                        std::cin.getline(subject, 1024);
                        unsigned long long id = sn.getLargestIdOfPost() +1;
                        Post *post = createPost(subject, 0, id, author->getId());
                        sn.createPost(post, typeUser);
                        std::cout << "Post " << id << " has been created" << std::endl;

                    } else if (strcmp(typePost, "[image]") == 0) {
                        std::cin >> subject;
                        unsigned long long id = sn.getLargestIdOfPost() +1;
                        Post *post = createPost(subject, 1, id, author->getId());
                        sn.createPost(post, typeUser);
                        std::cout << "Post " << id << " has been created" << std::endl;

                    } else {
                        std::cout << "Not such type of post!" << std::endl;
                    }
                } else {
                    std::cout << "This user is blocked or disn't exits" << std::endl;
                }
            } catch (std::exception& e){
                std::cerr << e.what() << std::endl;
            }
        } else if(strcmp(action, "remove_post") == 0) {
            try {
                int typeUser;
                unsigned long long id;
                std::cin >> id;
                User *user = sn.findUser(actor, typeUser);
                if (!user->getIsBloked()) {
                    if (typeUser == 0 || typeUser == -1) {
                        sn.deletePost(id);
                    } else if (typeUser == 1) {
                        for (int i = 0; i < user->getCountPost(); ++i) {
                            if(user->posts[i]->getId() == id)
                                sn.deletePost(id);
                        }
                    }
                    std::cout << "Post has been revomed" << std::endl;
                } else {
                    std::cout << "User is blocked" << std::endl;
                }
            } catch(std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        } else if(strcmp(action, "view_post") == 0) {
            try {
                int typeUser;
                unsigned long long id;
                std::cin >> id;
                User* user = sn.findUser(actor, typeUser);
                if(sn.nickNameExist(user->getNickName())) {
                    sn.viewPostById(id);
                    std::cout << "HTML has been generated" << std::endl;
                } else
                    std::cout << "User not exist in system" << std::endl;

            } catch (std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        } else if(strcmp(action, "view_all_posts") == 0) {
             try {
                 int typeUser;
                 std::cin >> subject;
                 User* user = sn.findUser(actor, typeUser);
                 User* user1 = sn.findUser(subject, typeUser);
                 if(sn.nickNameExist(user->getNickName()) && sn.nickNameExist(user1->getNickName())) {
                     sn.viewPostByNickName(user1->getNickName());
                     std::cout << "HTML has been generated" << std::endl;
                 } else
                     std::cout << "User not exist in system" << std::endl;

             } catch (std::exception& e) {
                std::cerr << e.what() << std::endl;
             }
        } else {
            std::cout << "Unknown command!" << std::endl;
        }
    }

    return 0;
}