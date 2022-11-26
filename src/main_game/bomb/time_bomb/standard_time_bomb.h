#pragma once

#include "../bomb.h"

class StandardTimeBomb : public Bomb {
public:
  using Ptr = std::unique_ptr<StandardTimeBomb>;
  StandardTimeBomb(MainGameComponents &components);
  bool isExpired() override;

  static StandardTimeBomb::Ptr create(MainGameComponents &components) {
    return std::make_unique<StandardTimeBomb>(components);
  }
  void checkSnapShot() override;

protected:
  int life_span;
};