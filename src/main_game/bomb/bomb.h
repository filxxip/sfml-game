#pragma once

#include "../../../data/config_file.h"
#include "../../game/main_game_components/main_game_components.h"
#include "../../picture/picture.h"

#include <cstdlib>

#include <chrono>

class Bomb {
protected:
  MainGameComponents &components;
  CustomPicture::Ptr picture;
  std::chrono::_V2::steady_clock::time_point last_measure;
  //   int boms_lasts;
  //   void measure(bool isrunning);
  bool executed = false;

  void checkSnapShot();

public:
  enum class BombType { UNDEFINED = -1, TIME, CLICK, HEART, MYSTERY };
  static const std::unordered_map<BombType, std::string> bomb_names;

  using time = std::chrono::_V2::steady_clock;
  using Ptr = std::unique_ptr<Bomb>;

  Bomb(MainGameComponents &components_);
  void execute();
  virtual bool isExpired(bool game_is_running) = 0;
  void putUnder(tgui::Widget::Ptr widget);
  bool isExecuted() const { return executed; }

  void destroyFromGUI();
};
