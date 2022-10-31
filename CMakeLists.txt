cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
project(game_project)
set(SFML_DIR "/usr/lib/x86_64-linux-gnu/cmake/SFML")
find_package(
    SFML 2.5.1
    COMPONENTS graphics window system audio
    REQUIRED)

add_executable(${PROJECT_NAME}
    sfml.cpp
    src/main_menu/main_menu.cpp
    src/game/game.cpp
)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-window sfml-system)