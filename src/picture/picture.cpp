#include "picture.h"

CustomPicture::CustomPicture(const std::string &path) { setPicture(path); }

void CustomPicture::setPicture(const std::string &path) {
  auto texture = tgui::Texture(path);
  getRenderer()->setTexture(texture);
}
void CustomPicture::setMiddle(const sf::RenderWindow &window,
                              tgui::Vector2f &&delta_moved) {
  const auto [window_width, window_height] = window.getSize();
  const auto [picture_width, picture_height] = getSize();
  setPosition((window_width - picture_width) / 2 + delta_moved.x,
              (window_height - picture_height) / 2 + delta_moved.y);
}

CustomPicture::Ptr CustomPicture::create(const std::string &path) {
  return std::make_shared<CustomPicture>(path);
}

const bool CustomPicture::isMiddle() const { return is_middled; }