cmake_minimum_required(VERSION 3.29)
project(Linked_List)

set(CMAKE_CXX_STANDARD 23)

find_package(fmt REQUIRED)

add_executable(${PROJECT_NAME} main.cpp
        List.cpp
        List.h
)
target_link_libraries(${PROJECT_NAME} fmt::fmt)
