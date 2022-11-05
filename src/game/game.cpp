#include "game.h"
#include "../../data/config_file.h"
#include <TGUI/Widgets/MessageBox.hpp>
#include <iostream>

Game::Game(sf::RenderWindow &window_) : components(window_) {}

void Game::start() {
  components.start();
  menu = MainMenuFactory::create(components.window);
  components.gui.add(menu.getPicture());
  components.gui.add(menu.getLayout());
  // auto msgbox = MsgBoxFactory::create(components.window);
  // components.gui.add(msgbox);
  // createMessageBox();
  // auto msgbox = createMessageBox();
  // msgbox->addButton(CustomMessageBox::Options::EXIT, [this]() {
  //   auto m = createMessageBox();
  //   m->addButton(CustomMessageBox::Options::STAY,
  //                []() { std::cout << "jello" << std::endl; });
  // });
  // msgbox->addButton(CustomMessageBox::Options::STAY);
  setBackground(Paths::TEXTURE_PATH);
}

void Game::setBackground(const std::string &texture_path) {
  background.setImage(texture_path);
  background.adjustToWindow(components.window);
}
CustomMessageBox::Ptr Game::createMessageBox() {
  auto msgbox = MsgBoxFactory::create(components.window);
  components.gui.add(msgbox);
  active_messagebox = msgbox;
  // msgbox->addButton(CustomMessageBox::Options::EXIT,
  //                   [this]() { components.window.close(); });
  // msgbox->addButton(CustomMessageBox::Options::STAY);
  return msgbox;
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
      if (!active_messagebox.expired()) {
        auto msg = active_messagebox.lock();
        if (msg->isVisible()) {
          PositionWidgetMenager::keepPosition(components.window, msg);
        }
      }
      if (menu.getPicture()->isVisible()) {
        PositionWidgetMenager::keepPosition(components.window,
                                            menu.getPicture());
      }
      if (menu.getLayout()->isVisible()) {
        PositionWidgetMenager::keepPosition(components.window,
                                            menu.getLayout());
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
