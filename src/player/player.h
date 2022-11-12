#pragma once

#include <SFML/Graphics/Image.hpp>

#include "../game/main_game_components/main_game_components.h"
#include "../picture/picture.h"

class Player {
public:
  enum class Movement { LEFT, RIGHT, UP, DOWN };
  std::unordered_map<Movement, std::pair<double, double>>
      movement_keyboard_values{{Player::Movement::DOWN, {0, 0.1}},
                               {Player::Movement::UP, {0, -0.1}},
                               {Player::Movement::LEFT, {-0.1, 0}},
                               {Player::Movement::RIGHT, {0.1, 0}}};

  Player(MainGameComponents &components_);
  const CustomPicture::Ptr &getImage() const;
  void move(Movement direction);
  void initialize();
  void remove();

private:
  int speed_rate = 3;
  MainGameComponents &components;
  CustomPicture::Ptr picture;
};