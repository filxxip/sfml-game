#include "picture.h"

CustomPicture::CustomPicture(const sf::RenderWindow &window_,
                             const std::string &path) {
  setPicture(path);
  getRenderer()->setTransparentTexture(true);
}

void CustomPicture::setPicture(const std::string &path) {
  auto texture = tgui::Texture(path);
  getRenderer()->setTexture(texture);
}

CustomPicture::Ptr CustomPicture::create(const sf::RenderWindow &window_,
                                         const std::string &path) {
  return std::make_shared<CustomPicture>(window_, path);
}

tgui::Layout2d CustomPicture::getMiddlePosition() const {
  return tgui::Layout2d(getPosition().x + getSize().x * 0.5,
                        getPosition().y + getSize().y * 0.5);
}
void CustomPicture::setMiddlePosition(CustomPicture::Ptr widget) {
  auto [x, y] = widget->getMiddlePosition();
  auto [pct_width, pct_height] = getSize();
  setPosition(x - pct_width * 0.5, y - pct_height * 0.5);
}