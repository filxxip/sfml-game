#include "fire.h"

TimeItem::TimeItem(MainGameComponents &components, const std::string &path)
    : GamePicture(components, path) {
  timer.run();
  setSize(BoxData::ScaleMenager::getBoxSize(),
          BoxData::ScaleMenager::getBoxSize());
}

bool TimeItem::isExpired(bool game_is_running) {
  measure(game_is_running);
  return timer.getLasts() > BombData::FIRE_ACTIVE_TIME;
}

// void TimeItem::execute() {}