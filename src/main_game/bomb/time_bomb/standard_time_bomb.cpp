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
    : Bomb(components), life_span(3000), boms_lasts(0) {
  auto start = time::now();
  last_measure = std::move(start);
}

void StandardTimeBomb::checkSnapShot() {
  if (life_span - boms_lasts < 500) {
    picture->setVisible(false);
  }
  if (life_span - boms_lasts < 400) {
    picture->setVisible(true);
  }
  if (life_span - boms_lasts < 300) {
    picture->setVisible(false);
  }
  if (life_span - boms_lasts < 200) {
    picture->setVisible(true);
  }
}

bool StandardTimeBomb::isExpired(bool game_is_running) {
  measure(game_is_running);
  checkSnapShot();
  return boms_lasts > life_span;
}