cmake_minimum_required(VERSION 3.17)
project(B_Tree_CPP_Database)

set(CMAKE_CXX_STANDARD 17)

include_directories(libs)


add_executable(B_Tree_CPP_Database
        main.cpp libs/sql.cpp libs/sql.h libs/table.cpp libs/table.h libs/BTree.cpp libs/BTree.h)
