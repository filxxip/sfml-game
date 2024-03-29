cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
project(game_project)
set(SFML_DIR "/usr/lib/x86_64-linux-gnu/cmake/SFML")

find_package(
    SFML 2.5.1
    COMPONENTS graphics window system audio
    REQUIRED)

find_package(SDL2 REQUIRED)
find_package(TGUI 0.10 REQUIRED)

# set(TGUI_STATIC_LIBRARIES TRUE)
add_executable(${PROJECT_NAME}
    src/menu/main_menu/base_main_menu/base_main_menu.cpp
    src/menu/main_menu/main_menu_layout/main_menu_layout.cpp
    src/menu/menu.cpp
    src/game/game.cpp
    src/background/background.cpp
    src/message_box/message_box.cpp
    src/game/custom_keyboard/custom_keyboard.cpp
    src/game/main_game_components/main_game_components.cpp
    src/picture/picture.cpp
    src/picture/game_picture.cpp
    src/position_widget_menager/position_widget_menager.cpp
    src/main_game/player/player.cpp
    src/main_game/main_game.cpp
    src/main_game/bomb/bomb.cpp
    src/main_game/bomb/fire.cpp
    src/main_game/bomb/click_bomb/click_bomb.cpp
    src/main_game/bomb/time_bomb/standard_time_bomb.cpp
    src/main_game/bomb/time_bomb/random_bomb/random_bomb.cpp
    src/main_game/bomb/time_bomb/heart_bomb/heart_bomb.cpp
    src/main_game/down_panel/down_panel.cpp
    src/main_game/box/box.cpp
    src/main_game/box/box_menager.cpp
    src/main_game/box/data_classes.cpp
    src/main_game/timer/timer.cpp
    src/main_game/down_panel/down_panel_elements.cpp
    data/config_file.cpp
    sfml.cpp
)

# target_link_libraries(${PROJECT_NAME} PRIVATE TGUI::TGUI)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-window sfml-system TGUI::TGUI)