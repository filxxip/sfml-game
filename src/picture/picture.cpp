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
