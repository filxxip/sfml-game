#pragma once

#include "../../game/main_game_components/main_game_components.h"
#include "../../picture/picture.h"
#include "../bomb/bomb.h"

class DownPanel {
private:
  MainGameComponents &components;
  CustomPicture::Ptr hearts_panel;
  std::vector<CustomPicture::Ptr> hearts;
  CustomPicture::Ptr current_bomb;

  void setHeartsPosition(int x, int y);

public:
  DownPanel(MainGameComponents &components_);

  void setPosition(int y);
  void initialize();
  void setBomb(Bomb::BombType bomb_type);
  void remove();
};