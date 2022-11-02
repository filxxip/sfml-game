#pragma once
#include <SFML/Graphics.hpp>

class Background {

public:
  void adjustToWindow(const sf::RenderWindow &window);
  const sf::Sprite &getSprite() const;
  void setImage(const std::string &texture_path);

private:
  sf::Sprite background_sprite;
  sf::Texture background_texture;
};