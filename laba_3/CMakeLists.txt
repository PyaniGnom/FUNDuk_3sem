cmake_minimum_required(VERSION 3.30)
project(laba_3)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt REQUIRED)

add_executable(laba_3 main.cpp
        FullNameField.h
        FullNameField.cpp
        Record.h
        Record.cpp
        Sorts.h
        Sorts.cpp
        FileHandler.h
        FileHandler.cpp
        ConsoleColors.h
)
target_link_libraries(${PROJECT_NAME} fmt::fmt)
