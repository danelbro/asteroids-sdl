cmake_minimum_required(VERSION 3.28)

project(asteroids-sdl
  VERSION 0.5
  LANGUAGES CXX)

option(ASTEROIDS-SDL_VENDORED "Use vendored libraries" ON)

add_subdirectory(extern/utilityKnife)
if(ASTEROIDS-SDL_VENDORED)
  add_subdirectory(extern/utilityKnife/extern/SDL)
  add_subdirectory(extern/utilityKnife/extern/SDL_ttf)
else()
  find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
  find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
  find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL_ttf)
endif()

add_executable(${CMAKE_PROJECT_NAME}
  src/AIComponent.hpp src/AIComponent.cpp
  src/Asteroid.hpp src/Asteroid.cpp
  src/AsteroidsApp.hpp src/AsteroidsApp.cpp
  src/asteroids.cpp
  src/Bullet.hpp src/Bullet.cpp
  src/Colors.hpp
  src/Enemy.hpp src/Enemy.cpp
  src/Engine.hpp src/Engine.cpp
  src/flags.hpp src/flags.cpp
  src/GameOver.hpp src/GameOver.cpp
  src/Gun.hpp src/Gun.cpp
  src/Hyperdrive.hpp src/Hyperdrive.cpp
  src/MainLevel.hpp src/MainLevel.cpp
  src/PhysicsManager.hpp src/PhysicsManager.cpp
  src/Player.hpp src/Player.cpp
  src/ScoreManager.hpp src/ScoreManager.cpp
  src/Ship.hpp src/Ship.cpp
  src/TitleScreen.hpp src/TitleScreen.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE utilityKnife::utilityKnife)
if(TARGET SDL2::SDL2main)
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL2::SDL2main)
endif()
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL2::SDL2-static)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL_ttf::SDL_ttf)
