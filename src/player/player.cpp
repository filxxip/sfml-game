#include "player.h"

#include "../../data/config_file.h"
#include "../picture/picture.h"

Player::Player(MainGameComponents &components_)
    : components(components_),
      picture(CustomPicture::create(components.window, Paths::BOMBER_PLAYER)) {}

const CustomPicture::Ptr &Player::getImage() const { return picture; }

// void Player::setVisible(bool status) { picture->setVisible(status); }

// bool Player::isVisible() const { return picture->isVisible(); }

void Player::move(Movement direction) {
  auto [x, y] = movement_keyboard_values.at(direction);
  auto [current_x, current_y] = picture->getPosition();
  picture->setPosition(current_x + speed_rate * x, current_y + speed_rate * y);
}

void Player::initialize() {
  picture->setPosition(100, 100);
  picture->setSize(40, 40);
}

void Player::remove() { components.gui.remove(picture); }