cmake_minimum_required(VERSION 3.20)

project(platformer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Only build the SFML modules we need
set(SFML_BUILD_GRAPHICS ON CACHE BOOL "" FORCE)
set(SFML_BUILD_WINDOW ON CACHE BOOL "" FORCE)
set(SFML_BUILD_SYSTEM ON CACHE BOOL "" FORCE)

set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)

# SFML source bundled with the project
add_subdirectory(libs/SFML)

# Game
add_executable(platformer
    src/main.cpp
)

target_link_libraries(platformer PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)