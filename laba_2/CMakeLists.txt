cmake_minimum_required(VERSION 3.29)
project(laba_2)

set(CMAKE_CXX_STANDARD 23)

find_package(fmt REQUIRED)

add_executable(laba_2 main.cpp
        RbTree.h
        Node.h
        Key.h
)
target_link_libraries(laba_2 fmt::fmt)
