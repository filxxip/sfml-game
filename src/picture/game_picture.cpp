#include "game_picture.h"

GamePicture::GamePicture(const sf::RenderWindow &window_,
                         const std::string &path)
    : CustomPicture(window_, path) {}

GamePicture::Ptr GamePicture::create(const sf::RenderWindow &window_,
                                     const std::string &path) {
  return std::make_shared<GamePicture>(window_, path);
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

  if (x_left2 > x_right || x_left > x_right2) {
    std::cout << "jestem tutaj2 " << std::endl;
    return false;
  }
  if (y_down2 < y_up) {
    std::cout << y_down2 << " " << y_up << std::endl;
    std::cout << "jestem tutaj3 " << std::endl;
    return false;
  }
  if (y_down < y_up2) {
    std::cout << "jestem tutaj4 " << std::endl;
    return false;
  }
  std::cout << "jestem tutaj " << std::endl;
  return true;
}