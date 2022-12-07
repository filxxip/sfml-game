#include "main_game.h"
#include <fstream>
#include <nlohmann/json.hpp>

#include "box/box.h"

MainGame::MainGame(MainGameComponents &components_)
    : components(components_), player(components_), own_signal("ClosingWindow"),
      bomb_panel(components), heart_panel(components),
      box_menager(components, player) {
  player.own_signal.connect([this]() {
    box_menager.createWholeFire(std::move(player.signal_helper.index),
                                player.signal_helper.current_bomb_power);
  });
  // player.addHeartSignal.connect([this]() { panel.addHeart(); });
  player.removeHeartSignal.connect([this]() {
    heart_panel.switchOnNextElement();
    if (heart_panel.getActiveElementNumber() <= 0) {
      gameOver();
    }
  });
}

void MainGame::initialize() {
  state = State::RUNNING;
  // components.gui.add(player.getImage());
  BoxData::ScaleMenager::changeOption(BoxData::SizeOptions::NORMAL);
  box_menager.initialize();
  player.initialize();
  bomb_panel.initialize();
  heart_panel.initialize();
  components.background.setImage(Paths::GAME_BACKGROUND);
}

void MainGame::gameOver() {
  state = State::PAUSE;
  auto exit_pair =
      std::make_pair(CustomMessageBox::Options::EXIT, [this]() { remove(); });
  auto messagebox = MsgBoxFactory::create(components, Json::GAME_OVER,
                                          {std::move(exit_pair)});

  components.gui.add(messagebox);
  messagebox->setEscapeKey(false);
  active_messagebox = messagebox;
  // PositionWidgetMenager::setMiddle(components.window, messagebox);
}

void MainGame::remove() {
  player.removeEachItem();
  heart_panel.remove();
  bomb_panel.remove();

  box_menager.remove();
  own_signal.emit(&customwidget);
  if (!active_messagebox->expired()) {
    components.gui.remove(active_messagebox->lock()); // chyba
  }
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
  auto is_from_fire_free = box_menager.isFromFirePositionFree(
      potential_new_position, player.getImage()->getSize());
  if (box_menager.isPositionFree(potential_new_position,
                                 player.getImage()->getSize()) &&
      (is_from_fire_free || player.isGhost())) {
    player.move(movement);
    if (player.isGhost() && is_from_fire_free) {
      player.setGhost(false);
    }
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
      player.putBomb(bomb_panel.getCurrentType());
      bomb_panel.switchOnNextElement();
    }
    if (components.isClicked(sf::Keyboard::LControl)) {
      // player.setNextBombOption();
      bomb_panel.changeCurrentElement();
    }
    if (components.isClicked(sf::Keyboard::Q)) {
      // player.setNextBombOption();
      heart_panel.addHeart();
      heart_panel.switchOnNextElement();
    }
    if (components.isClicked(sf::Keyboard::W)) {
      // player.setNextBombOption();
      heart_panel.switchOnPreviousElement();
    }
    // player.checkBombsExpired();
  }
}

void MainGame::checkBombs() {
  auto bomb_size = player.getUsedBombs();
  player.checkBombsExpired(isRunning());
  auto new_bombs = bomb_size - player.getUsedBombs();
  while (new_bombs-- > 0) {
    bomb_panel.switchOnPreviousElement();
    // new_bombs--;
  }
  box_menager.checkFiresExpired(isRunning());
  box_menager.checkBoxesExpired(isRunning());
}

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
  // PositionWidgetMenager::setMiddle(components.window, messagebox);
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
