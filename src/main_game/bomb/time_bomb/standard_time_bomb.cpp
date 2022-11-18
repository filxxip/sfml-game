#include "standard_time_bomb.h"

void StandardTimeBomb::measure(bool isrunning) {
  auto now = time::now();
  if (isrunning) {
    boms_lasts += std::chrono::duration_cast<std::chrono::milliseconds>(
                      now - last_measure)
                      .count();
  }
  last_measure = std::move(now);
}

StandardTimeBomb::StandardTimeBomb(MainGameComponents &components)
    : Bomb(components), life_span(BombData::STANDARD_LIVE_TIME), boms_lasts(0) {
  auto start = time::now();
  last_measure = std::move(start);
}

void StandardTimeBomb::checkSnapShot() {
  bool condition = false;
  auto start = 0;
  auto periods_number = static_cast<int>(BombData::SNAPSHOTTING_START /
                                         BombData::SNAPSHOTTING_PERIOD);
  for (int i = 0; i < periods_number; i++) {
    if (life_span - boms_lasts <
        BombData::SNAPSHOTTING_START - i * BombData::SNAPSHOTTING_PERIOD) {
      picture->setVisible(condition);
      condition = !condition;
    }
  }
}

bool StandardTimeBomb::isExpired(bool game_is_running) {
  measure(game_is_running);
  checkSnapShot();
  return boms_lasts > life_span;
}