#include "box.h"
#include "../../../data/config_file.h"

GamePicture::Ptr BoxFactory::create(MainGameComponents &components_,
                                    Types type) {
  std::string path;
  switch (type) {
  case Types::BOX: {
    path = Paths::BOX_PATH;
    break;
  }
  case Types::STONE: {
    path = Paths::STONE;
    break;
  }
  }
  return GamePicture::create(components_, path);
}

Box::Box(MainGameComponents &components_)
    : LiveItem(components_, Paths::BOX_PATH, 1) {
  setSize({BoxData::ScaleMenager::getBoxSize(),
           BoxData::ScaleMenager::getBoxSize()});
};
LiveItem::Ptr Box::create(MainGameComponents &components_) {
  auto box = std::make_shared<Box>(components_);
  return box;
}

Stone::Stone(MainGameComponents &components_)
    : LiveItem(components_, Paths::STONE, 5) {
  setSize({BoxData::ScaleMenager::getBoxSize(),
           BoxData::ScaleMenager::getBoxSize()});
}

LiveItem::Ptr Stone::create(MainGameComponents &components_) {
  auto stone = std::make_shared<Stone>(components_);
  return stone;
}

LiveItem::LiveItem(MainGameComponents &components_, const std::string &path,
                   int initial_lives)
    : lives(initial_lives), TimeItem(components_, path) {
  //   timer.meas
}

int LiveItem::getRemainLives() { return lives; }
void LiveItem::decreaseLives() {
  if (lives > 0) {
    lives--;
  };
}

void LiveItem::initializeEnd() {
  setLiveTime(1000);
  timer.run();
  lives = -1;
  setPicture(Paths::FIRE);
}
bool LiveItem::isExpired(bool game_is_running) {
  if (lives == 0) {
    initializeEnd();
  }
  return TimeItem::isExpired(game_is_running);
}