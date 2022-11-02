#include "game.h"
#include "../../data/config_file.h"
#include "../message_box/message_box.h"
#include <TGUI/Widgets/MessageBox.hpp>
#include <iostream>

Game::Game(sf::RenderWindow &window_) : window(window_), gui(window) {}

void Game::start() {
  gui.mainLoop();
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(60);
  window.create(sf::VideoMode(WindowData::WIDTH, WindowData::HEIGHT),
                WindowData::TITLE);
  setBackground(Paths::TEXTURE_PATH);
}

void Game::setBackground(const std::string &texture_path) {
  background.setImage(texture_path);
  background.adjustToWindow(window);
}

void Game::update() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && isRunning()) {
    createPauseMessageBox();
  }
}

void Game::createPauseMessageBox() {
  state = State::PAUSE;
  auto messagebox = ExitStayMessageBox::create(window);
  messagebox->addButton(CustomMessageBox::Options::STAY, [this, messagebox]() {
    messagebox->destroy();
    state = State::RUNNING;
  });
  messagebox->addButton(CustomMessageBox::Options::EXIT,
                        [this]() { window.close(); });
  gui.add(messagebox);
}

void Game::run() {
  while (isOpened()) {
    poolEvents();
    draw();
    update();
  }
}

void Game::draw() {
  window.clear();
  window.draw(background.getSprite());
  gui.draw();
  window.display();
}

const bool Game::isOpened() const { return window.isOpen(); }

const bool Game::isRunning() const { return state == State::RUNNING; }

const bool Game::isPause() const { return state == State::PAUSE; }

void Game::poolEvents() {
  while (window.pollEvent(evnt)) {
    gui.handleEvent(evnt);
    if (evnt.type == sf::Event::Closed) {
      window.close();
    }
  }
}