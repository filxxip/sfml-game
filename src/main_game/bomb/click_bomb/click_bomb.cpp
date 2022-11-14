#include "click_bomb.h"

bool ClickBomb::isExpired(bool game_is_running) { return false; }

ClickBomb::ClickBomb(MainGameComponents &components_) : Bomb(components_) {
  picture->setPicture(Paths::CLICK_BOMB_PATH);
}