cmake_minimum_required(VERSION 3.9)
project(TankSerializer)

set(CMAKE_CXX_STANDARD 11)

add_executable(TankSerializer main.cpp Tank.cpp Army.cpp Army.h)