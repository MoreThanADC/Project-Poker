cmake_minimum_required(VERSION 3.16.3)
project(Poker)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(Sources
    Card.cpp
    Comparator.cpp
    Deck.cpp
    Game.cpp
    Player.cpp
    Table.cpp
    Verifier.cpp)

add_library(${PROJECT_NAME}-lib STATIC ${Sources})  

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Werror -Wpedantic -Wconversion -O3)

add_subdirectory(tests)

# console: cmake .. -DCMAKE_C_COMPILER=/usr/bin/gcc-11 -DCMAKE_CXX_COMPILER=/usr/bin/g++-10