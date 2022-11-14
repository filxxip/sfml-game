#pragma once

#include <SFML/Graphics/Image.hpp>

#include "../../game/main_game_components/main_game_components.h"
#include "../../picture/picture.h"
#include "../bomb/bomb.h"

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

  void putBomb();

  void checkBombsExpired(bool game_is_running);

  void setNextBombOption();

  void removeEachItem();
  Bomb::BombType getCurrentBomb() const { return bomb_selector; }

private:
  bool isYValid(double new_y) const;
  bool isXValid(double new_x) const;
  int speed_rate = 3;
  Bomb::BombType bomb_selector = Bomb::BombType::TIME;
  std::vector<Bomb::BombType> bomb_options{
      Bomb::BombType::TIME, Bomb::BombType::CLICK, Bomb::BombType::HEART};

  MainGameComponents &components;
  CustomPicture::Ptr picture;
  std::vector<Bomb::Ptr> bombs;
};