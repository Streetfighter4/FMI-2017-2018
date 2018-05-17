cmake_minimum_required(VERSION 3.9)
project(SocialNetwork)

set(CMAKE_CXX_STANDARD 11)

add_executable(SocialNetwork main.cpp SocialNetwork.cpp SocialNetwork.h User.cpp User.h Moderator.cpp Moderator.h Admin.cpp Admin.h Post.cpp Post.h ImagePost.cpp ImagePost.h TextPost.cpp TextPost.h URLPost.cpp URLPost.h)