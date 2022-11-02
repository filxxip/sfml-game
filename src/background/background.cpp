#include "background.h"

void Background::setImage(const std::string &texture_path) {
  background_texture.loadFromFile(texture_path);
  background_sprite.setTexture(background_texture);
}

void Background::adjustToWindow(const sf::RenderWindow &window) {
  float scale_x =
      static_cast<float>(window.getSize().x) / background_texture.getSize().x;
  float scale_y =
      static_cast<float>(window.getSize().y) / background_texture.getSize().y;
  background_sprite.setScale(scale_x, scale_y);
}
const sf::Sprite &Background::getSprite() const { return background_sprite; }