#include "heart_bomb.h"

HeartBomb::HeartBomb(MainGameComponents &components_)
    : StandardTimeBomb(components_) {
  std::cout << "tworze heart" << std::endl;
  picture->setPicture(Paths::HEART_BOMB_PATH);
}