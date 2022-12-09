#include "main_game_components.h"
#include "../../../data/config_file.h"

MainGameComponents::MainGameComponents(sf::RenderWindow &window_)
    : window(window_), gui(window) {
      // view.setViewport
  // view.reset(sf::Vector2f(0, 0), sf::Vector2f(500, 500));
  start();
}

const bool MainGameComponents::isOpened() const { return window.isOpen(); }

void MainGameComponents::start() {
  gui.mainLoop();
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(60);
  window.create(sf::VideoMode(WindowData::WIDTH, WindowData::HEIGHT),
                WindowData::TITLE, sf::Style::Titlebar | sf::Style::Close);
  setBackground(Paths::TEXTURE_PATH);
  window.setKeyRepeatEnabled(false);
}

void MainGameComponents::setBackground(const std::string &texture_path) {
  background.setImage(texture_path);
  background.adjustToWindow(window);
}

bool MainGameComponents::isClicked(sf::Keyboard::Key key) {
  return evnt.type == sf::Event::KeyPressed && evnt.key.code == key;
}

bool MainGameComponents::isReleased(sf::Keyboard::Key key) {
  return evnt.type == sf::Event::KeyReleased && evnt.key.code == key;
}

void MainGameComponents::addOver(tgui::Widget::Ptr down_widget,
                                 tgui::Widget::Ptr up_widget) {
  gui.add(down_widget);
  gui.remove(up_widget);
  gui.add(up_widget);
}