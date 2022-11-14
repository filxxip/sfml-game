#include "player.h"

#include "../../../data/config_file.h"
#include "../bomb/click_bomb/click_bomb.h"
#include "../bomb/time_bomb/heart_bomb/heart_bomb.h"
#include "../bomb/time_bomb/random_bomb/random_bomb.h"
#include "../bomb/time_bomb/standard_time_bomb.h"

Player::Player(MainGameComponents &components_)
    : components(components_),
      picture(CustomPicture::create(components.window, Paths::BOMBER_PLAYER)) {}

const CustomPicture::Ptr &Player::getImage() const { return picture; }

// void Player::setVisible(bool status) { picture->setVisible(status); }

// bool Player::isVisible() const { return picture->isVisible(); }

void Player::move(Movement direction) {
  auto [x, y] = movement_keyboard_values.at(direction);
  auto [current_x, current_y] = picture->getPosition();
  auto new_x = current_x + speed_rate * x;
  auto new_y = current_y + speed_rate * y;
  if (isXValid(new_x) && isYValid(new_y)) {
    picture->setPosition(new_x, new_y);
  }
}

void Player::initialize() {
  components.gui.add(picture);
  picture->setPosition(100, 100);
  picture->setSize(40, 40);
}

void Player::remove() { components.gui.remove(picture); }

bool Player::isYValid(double new_y) const {
  return new_y > 0 && new_y < components.window.getSize().y;
}
bool Player::isXValid(double new_x) const {
  return new_x > 0 && new_x < components.window.getSize().x;
}

void Player::putBomb() {
  Bomb::Ptr bomb;

  switch (bomb_selector) {
  case Bomb::BombType::CLICK: {
    bomb = ClickBomb::create(components);
    break;
  }
  case Bomb::BombType::TIME: {
    bomb = StandardTimeBomb::create(components);
    break;
  }
  case Bomb::BombType::MYSTERY: {
    bomb = RandomTimeBomb::create(components);
    break;
  }
  case Bomb::BombType::HEART: {
    bomb = HeartBomb::create(components);
    break;
  }
  case Bomb::BombType::UNDEFINED: {
    return;
  }
  }
  bomb->putUnder(picture);
  bombs.push_back(std::move(bomb));
}

void Player::setNextBombOption() {
  auto index =
      std::find(bomb_options.begin(), bomb_options.end(), bomb_selector);
  bomb_selector =
      index == bomb_options.end() ? bomb_options.at(0) : *std::next(index);
}

void Player::checkBombsExpired(bool game_is_running) {
  for (auto &bomb : bombs) {
    if (bomb->isExpired(game_is_running)) {
      bomb->execute();
    }
  }
  auto new_end = std::remove_if(bombs.begin(), bombs.end(),
                                [](auto &bomb) { return bomb->isExecuted(); });
  bombs.erase(new_end, bombs.end());
}

void Player::removeEachItem() {
  components.gui.remove(picture);
  for (auto &bomb : bombs) {
    bomb->destroyFromGUI();
  }
}