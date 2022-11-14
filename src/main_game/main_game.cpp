#include "main_game.h"
#include <fstream>
#include <nlohmann/json.hpp>

MainGame::MainGame(MainGameComponents &components_)
    : components(components_), player(components_), own_signal("ClosingWindow"),
      panel(components) {
  panel.setPosition(components.window.getSize().y - 70);
}

void MainGame::initialize() {
  state = State::RUNNING;
  // components.gui.add(player.getImage());
  player.initialize();
  panel.initialize();
  components.background.setImage(Paths::GAME_BACKGROUND);
}

void MainGame::remove() {
  // active_messagebox.destroy();
  player.removeEachItem();
  panel.remove();
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

void MainGame::doPlayerActivities() {
  if (isRunning()) {
    if (components.isReleased(sf::Keyboard::Space)) {
      player.putBomb();
    }
    if (components.isClicked(sf::Keyboard::LControl)) {
      player.setNextBombOption();
      panel.setBomb(player.getCurrentBomb());
    }
    // player.checkBombsExpired();
  }
}

void MainGame::checkBombs() { player.checkBombsExpired(isRunning()); }

void MainGame::checkPause() {
  if (isRunning() && active_messagebox->expired() &&
      components.isClicked(sf::Keyboard::Escape)) {
    state = State::PAUSE;
    createExitMessageBox();
    components.keyboard.setClicked(sf::Keyboard::Escape);
    components.keyboard.setNotClickedAfterDelay(sf::Keyboard::Escape);
    return;
  }

  if (isRunning() && active_messagebox->expired() &&
      components.isClicked(sf::Keyboard::P)) {
    state = State::PAUSE;
    createPauseMessageBox();
    return;
  }
  if (isPause() && !active_messagebox->expired() &&
      components.isClicked(sf::Keyboard::Escape) &&
      components.keyboard.isNotClicked(sf::Keyboard::Escape)) {
    state = State::RUNNING;
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
