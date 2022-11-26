#include "standard_time_bomb.h"

StandardTimeBomb::StandardTimeBomb(MainGameComponents &components)
    : Bomb(components), life_span(BombData::STANDARD_LIVE_TIME) {
  timer.run();
  power = 5;
}

void StandardTimeBomb::checkSnapShot() {
  bool condition = false;
  auto start = 0;
  auto periods_number = static_cast<int>(BombData::SNAPSHOTTING_START /
                                         BombData::SNAPSHOTTING_PERIOD);
  for (int i = 0; i < periods_number; i++) {
    if (life_span - timer.getLasts() <
        BombData::SNAPSHOTTING_START - i * BombData::SNAPSHOTTING_PERIOD) {
      picture->setVisible(condition);
      condition = !condition;
    }
  }
}

bool StandardTimeBomb::isExpired() { return timer.getLasts() > life_span; }
