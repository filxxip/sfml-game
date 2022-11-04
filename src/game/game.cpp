#include "game.h"
#include "../../data/config_file.h"
#include "../message_box/message_box.h"
#include <TGUI/Widgets/MessageBox.hpp>
#include <iostream>

Game::Game(sf::RenderWindow &window_) : components(window_) {}

void Game::start() {
  components.start();
  menu = MainMenuFactory::create(components.window);
  components.gui.add(menu.getPicture());
  components.gui.add(menu.getLayout());
  // components.gui.remove(menu);
  setBackground(Paths::TEXTURE_PATH);
}

void Game::setBackground(const std::string &texture_path) {
  background.setImage(texture_path);
  background.adjustToWindow(components.window);
}

void Game::update() {
  // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && isRunning() &&
  //     keyboard.isNotClicked(sf::Keyboard::Escape)) {
  //   state = State::PAUSE;
  //   keyboard.setClickedAfterDelay(sf::Keyboard::Escape, 300);
  //   createPauseMessageBox();
  // }
  // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && isPause() &&
  //     keyboard.isClicked(sf::Keyboard::Escape)) {
  //   state = State::RUNNING;
  //   keyboard.setNotClicked(sf::Keyboard::Escape);
  // }
}

// void Game::createPauseMessageBox() {
//   auto messagebox = ExitStayMessageBox::create(components.window);
//   messagebox->addButton(CustomMessageBox::Options::STAY, [this, messagebox]()
//   {
//     messagebox->destroy();
//     state = State::RUNNING;
//   });
//   messagebox->addButton(CustomMessageBox::Options::EXIT,
//                         [this]() { components.window.close(); });
//   components.gui.add(messagebox);
// }

void Game::run() {
  while (components.isOpened()) {
    poolEvents();
    draw();
    update();
  }
}

void Game::poolEvents() {
  auto &evnt = components.evnt;
  while (components.window.pollEvent(evnt)) {
    components.gui.handleEvent(evnt);
    if (evnt.type == sf::Event::Closed) {
      components.window.close();
    }
    if (evnt.type == sf::Event::Resized) {
      if (menu->isVisible()) {
        menu->draw(components.window);
      }
    }
  }
}

void Game::draw() {
  components.window.clear();
  components.window.draw(background.getSprite());
  components.gui.draw();
  components.window.display();
}

// const bool Game::isRunning() const { return state == State::RUNNING; }

// const bool Game::isPause() const { return state == State::PAUSE; }
