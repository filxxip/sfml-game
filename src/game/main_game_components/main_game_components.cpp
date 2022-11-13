#include "main_game_components.h"
#include "../../../data/config_file.h"

MainGameComponents::MainGameComponents(sf::RenderWindow &window_)
    : window(window_), gui(window) {
  start();
}

const bool MainGameComponents::isOpened() const { return window.isOpen(); }

void MainGameComponents::start() {
  // window.setKeyRepeatEnabled(false);
  gui.mainLoop();
  window.setVerticalSyncEnabled(true);
  // window.setKeyRepeatEnabled(false);
  window.setFramerateLimit(60);
  window.create(sf::VideoMode(WindowData::WIDTH, WindowData::HEIGHT),
                WindowData::TITLE, sf::Style::Titlebar | sf::Style::Close);
  setBackground(Paths::TEXTURE_PATH);
}

void MainGameComponents::setBackground(const std::string &texture_path) {
  background.setImage(texture_path);
  background.adjustToWindow(window);
}