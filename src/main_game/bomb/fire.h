#pragma once

#include "../../../data/config_file.h"
#include "../../game/main_game_components/main_game_components.h"
#include "../../picture/game_picture.h"
#include "../timer/timer.h"

class Fire : public GamePicture {
  Timer timer;

public:
  Fire(MainGameComponents &components);
  using Ptr = std::shared_ptr<Fire>;
  static Fire::Ptr create(MainGameComponents &components) {
    return std::make_shared<Fire>(components);
  }

  void measure(bool game_is_running) { timer.measure(game_is_running); }
  int getLasts() const { return timer.getLasts(); }

  bool isExpired() const;

  void execute();
};