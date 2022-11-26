#pragma once

#include "../../../data/config_file.h"
#include "../../game/main_game_components/main_game_components.h"
#include "../../picture/picture.h"
#include "fire.h"

#include <cstdlib>

#include "../timer/timer.h"
#include <chrono>

class Bomb {
protected:
  MainGameComponents &components;
  CustomPicture::Ptr picture;
  int power;
  Timer timer;

  // bool executed = false;

public:
  enum class BombType { UNDEFINED = -1, TIME, CLICK, HEART, MYSTERY };
  static const std::unordered_map<BombType, std::string> bomb_names;
  using Ptr = std::unique_ptr<Bomb>;

  Bomb(MainGameComponents &components_);
  const CustomPicture::Ptr &getPicture() const { return picture; }
  void execute();
  virtual bool isExpired() = 0;
  void measure(bool isrunning);
  void putUnder(CustomPicture::Ptr widget);
  // bool isExecuted() const { return executed; }
  // bool isAlive() const { return !executed; }
  void destroyFromGUI();
  // void create_fire(Index &&index);
  virtual void checkSnapShot() = 0;
  int getPower() const { return power; }
};
