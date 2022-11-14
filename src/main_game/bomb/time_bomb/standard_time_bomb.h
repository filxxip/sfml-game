#pragma once

#include "../bomb.h"

class StandardTimeBomb : public Bomb {
public:
  using Ptr = std::unique_ptr<StandardTimeBomb>;
  StandardTimeBomb(MainGameComponents &components);
  bool isExpired(bool game_is_running);

  static StandardTimeBomb::Ptr create(MainGameComponents &components) {
    return std::make_unique<StandardTimeBomb>(components);
  }

protected:
  int life_span;

  int boms_lasts;
  void measure(bool isrunning);

  void checkSnapShot();
};