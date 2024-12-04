cmake_minimum_required(VERSION 3.29)
project(laba_2)

set(CMAKE_CXX_STANDARD 23)

find_package(fmt REQUIRED)
find_package(Boost 1.78.0 CONFIG REQUIRED COMPONENTS regex)

add_executable(${PROJECT_NAME} main.cpp
        RbTree.h
        Node.h
        Key.h
        Key.cpp
        FileHandler.h
        RegexUtils.h
        ConsoleColors.h
)
target_link_libraries(${PROJECT_NAME} fmt::fmt)
target_link_libraries(${PROJECT_NAME} ${BOOST_LIBRARIES})
