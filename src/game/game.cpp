#include "game.h"
#include "../../data/config_file.h"
#include <TGUI/Signal.hpp>
#include <TGUI/Widgets/MessageBox.hpp>
#include <ctime>
#include <iostream>

Game::Game(sf::RenderWindow &window_)
    : components(window_), menu(MainMenuFactory::create(components)),
      main_game(components) {
  main_game.own_signal.connect([this]() { menu.initialize(); });
}

void Game::start() {
  menu.addButtonCommand(EnumMenu::MainMenuOpts::EXIT, [this]() {
    menu.createCustomMessageBox(
        Json::EXIT_APP,
        {
            std::make_pair(CustomMessageBox::Options::EXIT,
                           [this]() { components.window.close(); }),
            std::make_pair(CustomMessageBox::Options::STAY,
                           [this]() { menu.getLayout()->unblockButtons(); }),
        });
  });

  menu.addButtonCommand(EnumMenu::MainMenuOpts::NEW, [this]() {
    menu.createCustomMessageBox(
        Json::NEW_GAME,
        {std::make_pair(CustomMessageBox::Options::YES,
                        [this]() { startNewGame(); }),
         std::make_pair(CustomMessageBox::Options::NO,
                        [this]() { menu.getLayout()->unblockButtons(); })});
  });

  menu.addToGui(components.gui);
}

void Game::startNewGame() {
  menu.remove();
  main_game.initialize();
  // main_game.setVisible(true);
}

void Game::update() {
  // if (components.evnt.type == sf::Event::KeyPressed) {
  //   if (components.evnt.key.code == sf::Keyboard::Down) {
  //     std::cout << "helloxxx" << std::endl;
  //   }
  // }
  if (menu.isInitialized()) {
    menu.getLayout()->moveMenu();
    menu.checkMsgBox();
  }

  if (main_game.isInitialized()) {
    // main_game.movePlayer();
    main_game.checkPause();
    main_game.doPlayerActivities();
  }
}
void Game::run() {
  while (components.isOpened()) {
    poolEvents();
    draw();
    if (main_game.isInitialized()) {
      main_game.movePlayer();
      main_game.checkBombs();
    }
  }
}

void Game::poolEvents() {
  while (components.window.pollEvent(components.evnt)) {
    components.gui.handleEvent(components.evnt);
    if (components.evnt.type == sf::Event::Closed) {
      components.window.close();
    }
    if (components.evnt.type == sf::Event::KeyPressed ||
        components.evnt.type == sf::Event::KeyReleased) {
      std::clock_t start = std::clock();

      update();
      double duration = (std::clock() - start);
      std::cout << duration << "hah" << std::endl;
    }
  }
}

// void Game::keepWidgetsPosition() {

//   if (!active_messagebox.expired()) {
//     auto msg = active_messagebox.lock();
//     if (msg->isVisible()) {
//       PositionWidgetMenager::keepPosition(components.window, msg);
//     }
//   }
//   if (menu.isInitialized()) {
//     PositionWidgetMenager::keepPosition(components.window, menu.getLayout());
//     PositionWidgetMenager::keepPosition(components.window,
//     menu.getPicture());
//   }
//   if (main_game.isInitialized()) {
//     PositionWidgetMenager::keepPosition(components.window,
//                                         main_game.getPlayer().getImage());
//   }
//   std::cout << "wykonalo" << std::endl;
// }

void Game::draw() {
  components.window.clear();
  components.window.draw(components.background.getSprite());
  components.gui.draw();
  components.window.display();
}

// const bool Game::isRunning() const { return state == State::RUNNING; }

// const bool Game::isPause() const { return state == State::PAUSE; }
