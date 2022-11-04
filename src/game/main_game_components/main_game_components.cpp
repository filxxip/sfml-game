#include "main_game_components.h"
#include "../../../data/config_file.h"

MainGameComponents::MainGameComponents(sf::RenderWindow &window_)
    : window(window_), gui(window) {}

const bool MainGameComponents::isOpened() const { return window.isOpen(); }

void MainGameComponents::start() {
  gui.mainLoop();
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(60);
  window.create(sf::VideoMode(WindowData::WIDTH, WindowData::HEIGHT),
                WindowData::TITLE);
}
