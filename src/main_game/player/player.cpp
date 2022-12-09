#include "player.h"

#include "../../../data/config_file.h"
#include "../bomb/click_bomb/click_bomb.h"
#include "../bomb/time_bomb/heart_bomb/heart_bomb.h"
#include "../bomb/time_bomb/random_bomb/random_bomb.h"
#include "../bomb/time_bomb/standard_time_bomb.h"

Player::Player(MainGameComponents &components_)
    : components(components_),
      picture(GamePicture::create(components, Paths::BOMBER_PLAYER)),
      own_signal("my_signal_for_fire", 1), addHeartSignal("my_heart_signal"),
      removeHeartSignal("my_remove_heart_signal") {}

const GamePicture::Ptr &Player::getImage() const { return picture; }

void Player::move(Movement direction) {
  auto new_position = getPredictedNewPosition(direction);
  if (isXValid(new_position.x.getValue()) &&
      isYValid(new_position.y.getValue())) {
    picture->setPosition(new_position);
  }
}

void Player::setGhost(bool value) {
  if (value) {
    picture->getRenderer()->setOpacity(0.75);
  } else {
    picture->getRenderer()->setOpacity(1);
  }
  ghost = value;
}

const tgui::Layout2d Player::getPredictedNewPosition(Movement direction) {
  auto [x, y] = movement_keyboard_values.at(direction);
  auto [current_x, current_y] = picture->getPosition();
  auto new_x = current_x + speed_rate * x;
  auto new_y = current_y + speed_rate * y;
  return tgui::Layout2d(new_x, new_y);
}
void Player::initialize() {
  setGhost(false);
  components.gui.add(picture);
  picture->setSize(BoxData::ScaleMenager::getPlayerSize(),
                   BoxData::ScaleMenager::getPlayerSize());
  picture->setIndexPosition(Index(1, 1));
}

// void Player::remove() {
//   for (auto &bomb : bombs) {
//     components.gui.remove(bomb->getPicture());
//   }
//   bombs.clear();
//   components.gui.remove(picture);
// }

bool Player::isYValid(double new_y) const {
  return new_y > 0 && new_y < components.window.getSize().y -
                                  BoxData::ScaleMenager::getPlayerSize();
}

bool Player::isXValid(double new_x) const {
  return new_x > 0 && new_x < components.window.getSize().x -
                                  BoxData::ScaleMenager::getPlayerSize();
}

void Player::putBomb(Bomb::BombType type) {
  Bomb::Ptr bomb;

  switch (type) {
  case Bomb::BombType::CLICK: {
    bomb = ClickBomb::create(components);
    break;
  }
  case Bomb::BombType::TIME: {
    std::cout << "sdassfs" << std::endl;
    bomb = StandardTimeBomb::create(components);
    break;
  }
  case Bomb::BombType::MYSTERY: {
    std::cout << "hello2" << std::endl;
    bomb = RandomTimeBomb::create(components);
    break;
  }
  case Bomb::BombType::HEART: {
    std::cout << "hello" << std::endl;
    bomb = HeartBomb::create(components);
    break;
  }
  case Bomb::BombType::UNDEFINED: {
    return;
  }
  }
  bomb->changePower(bomb_power);
  bomb->putUnder(picture);
  bombs.push_back(std::move(bomb));
}

void Player::setNextBombOption() {
  std::cout << "xxx" << std::endl;
  auto index =
      std::find_if(Bomb::bomb_names.begin(), Bomb::bomb_names.end(),
                   [this](auto &pair) { return bomb_selector == pair.first; });
  bomb_selector = index == std::prev(Bomb::bomb_names.end())
                      ? Bomb::BombType::TIME
                      : std::next(index)->first;
  std::cout << "xxx" << std::endl;
}

void Player::checkBombsExpired(bool game_is_running) {
  for (auto &bomb : bombs) {
    bomb->measure(game_is_running);
    bomb->checkSnapShot();
    if (bomb->isExpired()) {
      bomb->execute();

      signal_helper.index = Index::getIndexFromPosition(bomb->getPicture());
      signal_helper.current_bomb_power = bomb->getPower();
      signal_helper.affect_on_player = bomb->affectOnPlayer();
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
  bombs.clear();
}