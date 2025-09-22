cmake_minimum_required(VERSION 3.22)
project(ZOMBIES LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

set(ASSETS_DIR       "${CMAKE_SOURCE_DIR}/src/assets")
set(ASSETS_DEST_DIR  "${CMAKE_CURRENT_BINARY_DIR}/src/assets")

add_custom_target(assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_DIR}" "${ASSETS_DEST_DIR}"
        BYPRODUCTS "${ASSETS_DEST_DIR}"
        COMMENT "Copying assets to build directory"
)

add_executable(ZOMBIES
        src/main.cpp
        src/Player.cpp
        src/Player.h
        src/utils/Assets.h
        src/utils/DebugConsole.h
        src/utils/DebugConsole.cpp
        src/utils/Console.h
        src/ZombieArena.h
        src/CreateBackground.cpp
        src/TextureHolder.h
        src/TextureHolder.cpp
        src/Zombie.h
        src/Zombie.cpp
        src/CreateHorde.cpp
        src/Bullet.h
        src/Bullet.cpp
)

add_dependencies(ZOMBIES assets)

target_link_libraries(ZOMBIES
        PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)

target_compile_definitions(ZOMBIES
        PRIVATE
        RESOURCE_DIR="${ASSETS_DEST_DIR}"
)