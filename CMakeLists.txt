cmake_minimum_required(VERSION 3.17)
project(B_Tree_CPP_Database)

set(CMAKE_CXX_STANDARD 14)

include_directories(libs)

add_executable(B_Tree_CPP_Database
        libs/BTree.cpp
        libs/BTree.h
        main.cpp libs/command_handler.cpp)
