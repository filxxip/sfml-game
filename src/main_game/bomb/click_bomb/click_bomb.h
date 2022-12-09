#pragma once

#include "../bomb.h"

class ClickBomb : public Bomb {
public:
  using Ptr = std::unique_ptr<ClickBomb>;
  ClickBomb(MainGameComponents &components_);
  static ClickBomb::Ptr create(MainGameComponents &components) {
    return std::make_unique<ClickBomb>(components);
  }
  bool isExpired() override;
  void checkSnapShot() override;
  // bool shouldBeRemoved(bool game_is_running) override;
    bool affectOnPlayer()const override{return true;}
};