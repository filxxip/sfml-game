#include "random_bomb.h"

RandomTimeBomb::RandomTimeBomb(MainGameComponents &components_)
    : StandardTimeBomb(components_) {
  picture->setPicture(Paths::MYSTERY_BOMB_PATH);
  setRandomTime(BombData::MINIMUM_LIVE_TIME,
                BombData::MAXIMUM_RANDOM_LIVE_TIME);
}

void RandomTimeBomb::setRandomTime(int start, int end) {
  std::srand((unsigned)std::time(NULL));
  int random = std::rand() % (end - start) + start;
  life_span = random;
}