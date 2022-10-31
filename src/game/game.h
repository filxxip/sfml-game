#pragma once
#include <SFML/Graphics.hpp>

class Game {
public:
  Game(sf::RenderWindow &window_);
  void start();

private:
  sf::RenderWindow &window;
};