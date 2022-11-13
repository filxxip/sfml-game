#include "main_game.h"
#include <fstream>
#include <nlohmann/json.hpp>

MainGame::MainGame(MainGameComponents &components_)
    : components(components_), player(components_),
      own_signal("ClosingWindow") {}

void MainGame::initialize() {
  state = State::RUNNING;
  components.gui.add(player.getImage());
  player.initialize();
  components.background.setImage(Paths::GAME_BACKGROUND);
}

void MainGame::remove() {
  // active_messagebox.destroy();
  components.gui.remove(player.getImage());
  own_signal.emit(&customwidget);
}

const bool MainGame::isInitialized() const {
  const auto &widgets = components.gui.getWidgets();
  auto index = std::find(widgets.begin(), widgets.end(), player.getImage());
  auto y = index != widgets.end();
  return index != widgets.end();
}

const Player &MainGame::getPlayer() const { return player; }

void MainGame::movePlayer() {
  if (isRunning()) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      player.move(Player::Movement::LEFT);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      player.move(Player::Movement::RIGHT);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      player.move(Player::Movement::DOWN);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      player.move(Player::Movement::UP);
    }
  }
}

void MainGame::checkPause() {
  if (isRunning() && active_messagebox->expired() &&
      components.isClicked(sf::Keyboard::Escape)) {
    std::cout << "xxxx" << std::endl;
    state = State::PAUSE;
    createExitMessageBox();
    components.keyboard.setClicked(sf::Keyboard::Escape);
    components.keyboard.setNotClickedAfterDelay(sf::Keyboard::Escape);
  }

  if (isRunning() && active_messagebox->expired() &&
      components.isClicked(sf::Keyboard::P)) {
    state = State::PAUSE;
    // components.keyboard.clickAndUnclickKey(sf::Keyboard::P);
    createPauseMessageBox();
  }
  std::cout << (components.keyboard.isNotClicked(sf::Keyboard::Escape))
            << std::endl;

  std::cout << (!active_messagebox->expired()) << std::endl;
  if (isPause() && !active_messagebox->expired() &&
      components.isClicked(sf::Keyboard::Escape) &&
      components.keyboard.isNotClicked(sf::Keyboard::Escape)) {
    state = State::RUNNING;
    std::cout << "xxxsdsd" << std::endl;
    // components.keyboard.clickAndUnclickKey(sf::Keyboard::Escape);
    // active_messagebox.destroy();
  }
  active_messagebox.checkKeyboard();
}

const bool MainGame::isRunning() const { return state == State::RUNNING; }

const bool MainGame::isPause() const { return state == State::PAUSE; }

void MainGame::createExitMessageBox() {
  auto stay_pair = std::make_pair(CustomMessageBox::Options::STAY,
                                  [this]() { state = State::RUNNING; });
  auto exit_pair =
      std::make_pair(CustomMessageBox::Options::EXIT, [this]() { remove(); });
  auto messagebox =
      MsgBoxFactory::create(components, Json::EXIT_GAME,
                            {std::move(exit_pair), std::move(stay_pair)});

  components.gui.add(messagebox);
  active_messagebox = messagebox;
  PositionWidgetMenager::setMiddle(components.window, messagebox);
}

void MainGame::createPauseMessageBox() {
  auto stay_pair = std::make_pair(CustomMessageBox::Options::RESUME,
                                  [this]() { state = State::RUNNING; });

  auto messagebox =
      MsgBoxFactory::create(components, Json::RESUME, {std::move(stay_pair)});

  components.gui.add(messagebox);
  active_messagebox = messagebox;
  PositionWidgetMenager::setMiddle(components.window, messagebox);
}
