#include "player.h"

#include "../../../data/config_file.h"
#include "../bomb/click_bomb/click_bomb.h"
#include "../bomb/time_bomb/heart_bomb/heart_bomb.h"
#include "../bomb/time_bomb/random_bomb/random_bomb.h"
#include "../bomb/time_bomb/standard_time_bomb.h"

Player::Player(MainGameComponents &components_)
    : components(components_),
      picture(GamePicture::create(components.window, Paths::BOMBER_PLAYER)),
      own_signal("my_signal_for_fire", 1) {}

const GamePicture::Ptr &Player::getImage() const { return picture; }

void Player::move(Movement direction) {
  auto new_position = getPredictedNewPosition(direction);
  if (isXValid(new_position.x.getValue()) &&
      isYValid(new_position.y.getValue())) {
    picture->setPosition(new_position);
  }
}

const tgui::Layout2d Player::getPredictedNewPosition(Movement direction) {
  auto [x, y] = movement_keyboard_values.at(direction);
  auto [current_x, current_y] = picture->getPosition();
  auto new_x = current_x + speed_rate * x;
  auto new_y = current_y + speed_rate * y;
  return tgui::Layout2d(new_x, new_y);
}
void Player::initialize() {
  components.gui.add(picture);
  picture->setSize(BoxData::ScaleMenager::getPlayerSize(),
                   BoxData::ScaleMenager::getPlayerSize());
  picture->setIndexPosition(Index(1, 1));
}

void Player::remove() { components.gui.remove(picture); }

bool Player::isYValid(double new_y) const {
  return new_y > 0 && new_y < components.window.getSize().y -
                                  BoxData::ScaleMenager::getPlayerSize();
}

bool Player::isXValid(double new_x) const {
  return new_x > 0 && new_x < components.window.getSize().x -
                                  BoxData::ScaleMenager::getPlayerSize();
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
  bomb_selector = index == std::prev(bomb_options.end()) ? bomb_options.at(0)
                                                         : *std::next(index);
}

void Player::checkBombsExpired(bool game_is_running) {
  for (auto &bomb : bombs) {
    bomb->measure(game_is_running);
    bomb->checkSnapShot();
    if (bomb->isExpired()) {
      bomb->execute();

      signal_helper.index = Index::getIndexFromPosition(bomb->getPicture());
      signal_helper.current_bomb_power = bomb->getPower();
      own_signal.emit(&customwidget);
    }
  }
  auto new_end = std::remove_if(bombs.begin(), bombs.end(),
                                [](auto &bomb) { return bomb->isExpired(); });
  bombs.erase(new_end, bombs.end());
}

void Player::removeEachItem() {
  components.gui.remove(picture);
  for (auto &bomb : bombs) {
    bomb->destroyFromGUI();
  }
}