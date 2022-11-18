#pragma once

#include "../../game/main_game_components/main_game_components.h"
#include "../../picture/picture.h"
#include "../bomb/bomb.h"

class Heart : public CustomPicture {
public:
  using Ptr = std::shared_ptr<Heart>;
  enum class Type { RED, GREY };
  Type getType() const { return type; }
  void changeType() {
    type = type == Type::RED ? Type::GREY : Type::RED;
    if (type == Type::RED) {
    } else {
    }
    changeStyle();
  }
  Heart(const sf::RenderWindow &window, const std::string &path)
      : CustomPicture(window, path) {}

  static Ptr create(const sf::RenderWindow &window, const std::string &path) {
    return std::make_shared<Heart>(window, path);
  }

private:
  void changeStyle() {
    type == Type::GREY ? setPicture(Paths::GREY_HEART_PATH)
                       : setPicture(Paths::RED_HEART_PATH);
  }
  Type type = Type::RED;
};

class DownPanel {
private:
  MainGameComponents &components;
  CustomPicture::Ptr hearts_panel;
  std::vector<Heart::Ptr> hearts;
  CustomPicture::Ptr current_bomb;
  int active_hearts;

  void setHeartsPosition(int x, int y);

  void createHearts(int hearts_number);
  Heart::Ptr createHeart();
  void changeHeartStatus(int index);

  bool isHeartNumberValid(int number);

public:
  DownPanel(MainGameComponents &components_);

  void setSize();
  void setPosition(int y);
  void initialize();
  void setBomb(Bomb::BombType bomb_type);
  void remove();
  void addHeart();
  void removeHeart();
  const int getHeartNumber() const;
};