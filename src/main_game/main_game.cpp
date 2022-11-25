#include "main_game.h"
#include <fstream>
#include <nlohmann/json.hpp>

#include "box/box.h"

MainGame::MainGame(MainGameComponents &components_)
    : components(components_), player(components_), own_signal("ClosingWindow"),
      panel(components), box_menager(components, player) {}

void MainGame::initialize() {
  state = State::RUNNING;
  // components.gui.add(player.getImage());
  BoxData::ScaleMenager::changeOption(BoxData::SizeOptions::NORMAL);
  box_menager.initialize();
  player.initialize();
  panel.initialize();
  components.background.setImage(Paths::GAME_BACKGROUND);
}

void MainGame::remove() {
  // active_messagebox.destroy();
  player.removeEachItem();
  panel.remove();
  box_menager.remove();
  own_signal.emit(&customwidget);
}

const bool MainGame::isInitialized() const {
  const auto &widgets = components.gui.getWidgets();
  auto index = std::find(widgets.begin(), widgets.end(), player.getImage());
  auto y = index != widgets.end();
  return index != widgets.end();
}

const Player &MainGame::getPlayer() const { return player; }

void MainGame::movePlayerIfValidNewPosition(Player::Movement movement) {
  auto potential_new_position = player.getPredictedNewPosition(movement);
  if (box_menager.isPositionFree(potential_new_position,
                                 player.getImage()->getSize())) {
    player.move(movement);
  }
}

void MainGame::movePlayer() {
  if (isRunning()) {
    std::clock_t start = std::clock();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      // std::clock_t start = std::clock();

      movePlayerIfValidNewPosition(Player::Movement::LEFT);
      // double duration = (std::clock() - start);
      // std::cout << duration << "l" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      // std::clock_t start = std::clock();
      movePlayerIfValidNewPosition(Player::Movement::RIGHT);
      // double duration = (std::clock() - start);
      // std::cout << duration << "r" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      // std::clock_t start = std::clock();
      movePlayerIfValidNewPosition(Player::Movement::DOWN);
      // double duration = (std::clock() - start);
      // std::cout << duration << "d" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      // std::clock_t start = std::clock();
      movePlayerIfValidNewPosition(Player::Movement::UP);
      // double duration = (std::clock() - start);
      // std::cout << duration << "u" << std::endl;
    }
    // double duration = (std::clock() - start);
    // std::cout << duration << std::endl;
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
    if (components.isClicked(sf::Keyboard::Q)) {
      // player.setNextBombOption();
      panel.addHeart();
    }
    if (components.isClicked(sf::Keyboard::W)) {
      // player.setNextBombOption();
      panel.removeHeart();
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
