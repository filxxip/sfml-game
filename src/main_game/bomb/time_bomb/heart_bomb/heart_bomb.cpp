#include "heart_bomb.h"

HeartBomb::HeartBomb(MainGameComponents &components_)
    : StandardTimeBomb(components_) {
  picture->setPicture(Paths::HEART_BOMB_PATH);
}