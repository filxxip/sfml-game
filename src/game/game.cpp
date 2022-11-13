#include "game.h"
#include "../../data/config_file.h"
#include <TGUI/Signal.hpp>
#include <TGUI/Widgets/MessageBox.hpp>
#include <iostream>

Game::Game(sf::RenderWindow &window_)
    : components(window_), menu(MainMenuFactory::create(components)),
      main_game(components) {
  main_game.own_signal.connect([this]() { menu.initialize(); });
}

void Game::start() {
  menu.addButtonCommand(EnumMenu::MainMenuOpts::EXIT, [this]() {
    menu.createCustomMessageBox(
        MsgBoxFactory::MessageBoxType::APP_EXIT,
        {std::make_pair(CustomMessageBox::Options::STAY,
                        [this]() { menu.getLayout()->unblockButtons(); }),
         std::make_pair(CustomMessageBox::Options::EXIT,
                        [this]() { components.window.close(); })});
  });

  menu.addButtonCommand(EnumMenu::MainMenuOpts::NEW, [this]() {
    menu.createCustomMessageBox(
        MsgBoxFactory::MessageBoxType::NEW_GAME,
        {std::make_pair(CustomMessageBox::Options::YES,
                        [this]() { startNewGame(); }),
         std::make_pair(CustomMessageBox::Options::NO,
                        [this]() { menu.getLayout()->unblockButtons(); })});
  });

  menu.addToGui(components.gui);
}

// void Game::createCustomMessageBox(
//     MsgBoxFactory::MessageBoxType type,
//     std::vector<std::pair<CustomMessageBox::Options, std::function<void()>>>
//         buttons) {
//   auto msgbox =
//       MsgBoxFactory::createCustomMessageBox(components.window, type,
//       buttons);
//   components.gui.add(msgbox);
//   menu.getLayout()->blockButtons();
//   active_messagebox = msgbox;
// }

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
    main_game.movePlayer();
    // main_game.checkPause();
  }
}
void Game::run() {
  while (components.isOpened()) {
    poolEvents();
    draw();
    if (main_game.isInitialized()) {
      main_game.movePlayer();
    }
  }
}

void Game::poolEvents() {
  while (components.window.pollEvent(components.evnt)) {
    components.gui.handleEvent(components.evnt);
    if (components.evnt.type == sf::Event::Closed) {
      components.window.close();
    }
    if (components.evnt.type == sf::Event::KeyReleased) {
      if (components.evnt.key.code == sf::Keyboard::X) {
        std::cout << "helloxxx222" << std::endl;
      }
    }
    update();

    // if (components.evnt.type == sf::Event::Resized) {
    //   keepWidgetsPosition();
    // }
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
