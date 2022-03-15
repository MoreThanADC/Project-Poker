cmake_minimum_required(VERSION 3.14)
project(Poker)

set(CMAKE_CXX_STANDARD 20)

set(SRC
    Card.cpp
    Comparator.cpp
    Deck.cpp
    Game.cpp
    Player.cpp
    Table.cpp
    Verifier.cpp)

add_library(${PROJECT_NAME}-lib STATIC ${SRC})

add_executable(${PROJECT_NAME} main.cpp)
#add_executable(${PROJECT_NAME}-ut test/pokerTest.cpp)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)
#target_link_libraries(${PROJECT_NAME}-ut ${PROJECT_NAME}-lib)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wpedantic -Wconversion -O3)
#target_compile_options(${PROJECT_NAME}-ut PRIVATE -Wall -Wextra -Werror -Wpedantic -Wconversion)
