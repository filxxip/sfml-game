#include "fire.h"

Fire::Fire(MainGameComponents &components)
    : GamePicture(components.window, Paths::FIRE) {
  timer.run();
  setSize(BoxData::ScaleMenager::getBoxSize(),
          BoxData::ScaleMenager::getBoxSize());
}

bool Fire::isExpired() const {
  return timer.getLasts() > BombData::FIRE_ACTIVE_TIME;
}

void Fire::execute() {
  // compone
}