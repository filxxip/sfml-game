#include "game_picture.h"

GamePicture::GamePicture(MainGameComponents &components_,
                         const std::string &path)
    : components(components_), CustomPicture(components_.window, path) {}

GamePicture::Ptr GamePicture::create(MainGameComponents &components_,
                                     const std::string &path) {
  return std::make_shared<GamePicture>(components_, path);
}

bool GamePicture::isWidgetInside(const tgui::Layout2d &position,
                                 const tgui::Layout2d &size) const {
  auto x_left = getPosition().x;
  auto x_right = x_left + getSize().x;
  auto y_up = getPosition().y;
  auto y_down = y_up + getSize().y;

  auto x_left2 = position.x.getValue();
  auto x_right2 = x_left2 + size.x.getValue();
  auto y_up2 = position.y.getValue();
  auto y_down2 = y_up2 + size.y.getValue();

  if (x_left2 >= x_right || x_left >= x_right2) {
    return false;
  }
  if (y_down2 <= y_up) {
    return false;
  }
  if (y_down <= y_up2) {
    return false;
  }
  return true;
}
void GamePicture::setIndexPosition(Index &&index) {
  setPosition(index.convertToPosition(getSize().x, getSize().y));
}

Index GamePicture::getIndexPosition() {
  return Index::getIndexFromPosition(getSize(), getPosition());
}
