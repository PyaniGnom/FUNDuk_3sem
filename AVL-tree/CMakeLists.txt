cmake_minimum_required(VERSION 3.29)
project(AVL_tree)

set(CMAKE_CXX_STANDARD 23)

find_package(fmt REQUIRED)

add_executable(AVL_tree main.cpp
        AvlTree.cpp
        AvlTree.h)
target_link_libraries(AVL_tree fmt::fmt)
