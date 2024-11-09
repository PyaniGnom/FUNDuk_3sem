cmake_minimum_required(VERSION 3.29)
project(RB_Tree)

set(CMAKE_CXX_STANDARD 23)

find_package(fmt REQUIRED)

add_executable(${PROJECT_NAME} main.cpp
        LlRbTree.h
        RbTree.h
        Node.h
)
target_link_libraries(${PROJECT_NAME} fmt::fmt)
