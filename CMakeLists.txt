cmake_minimum_required(VERSION 3.13)
project(carGame)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR/cmake})
set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(carGame main.cpp res/car.cpp res/Game.cpp res/SDL/SDLcar.cpp res/SDL/SDLFact.cpp res/eventHandler.cpp res/SDL/SDLeventHandler.cpp res/Missile.cpp res/SDL/SDLMissile.cpp res/Enemy.cpp res/SDL/SDLEnemy.cpp res/Bonus.cpp res/Bonus.h res/SDL/SDLBonus.cpp res/SDL/SDLBonus.h)
target_link_libraries(carGame ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf)