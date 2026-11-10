cmake_minimum_required(VERSION 3.20)

project(platformer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build only the SFML modules used by the game.
set(SFML_BUILD_GRAPHICS ON CACHE BOOL "" FORCE)
set(SFML_BUILD_WINDOW ON CACHE BOOL "" FORCE)
set(SFML_BUILD_SYSTEM ON CACHE BOOL "" FORCE)
set(SFML_BUILD_AUDIO ON CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)

# SFML is bundled so a network connection is not required to configure the
# project.
add_subdirectory(libs/SFML)

set(GAME_SOURCES
    src/main.cpp
    src/Animation.h
    src/Enemy.h
    src/Player.h
    src/Tile.h
    src/TileManager.h
)

add_executable(platformer
    ${GAME_SOURCES}
)

target_link_libraries(platformer PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)

target_include_directories(platformer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# The game intentionally loads assets relative to its working directory.
# Copy them next to the executable for both single- and multi-config
# generators (Makefiles, Ninja, Visual Studio, etc.).
set(GAME_ASSETS
    "ATTACK 1.png"
    "IDLE.png"
    "RUN.png"
    "bgmusic.wav"
    "map.png"
    "mapCollision.png"
)

foreach(asset IN LISTS GAME_ASSETS)
    add_custom_command(TARGET platformer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/src/${asset}"
            "$<TARGET_FILE_DIR:platformer>/${asset}"
        VERBATIM
    )
endforeach()

install(TARGETS platformer RUNTIME DESTINATION .)
install(FILES
    ${GAME_ASSETS}
    DESTINATION .
)