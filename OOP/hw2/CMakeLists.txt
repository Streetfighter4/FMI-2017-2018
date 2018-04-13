cmake_minimum_required(VERSION 3.9)
project(hm2)

set(CMAKE_CXX_STANDARD 11)

add_executable(hm2 main.cpp File.cpp File.h Line.cpp Line.h Word.cpp Word.h Constants.h)