#include "data/config_file.h"
#include "src/game/game.h"

#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window;
  // window.create(sf::VideoMode(WindowData::WIDTH, WindowData::HEIGHT),
  //               WindowData::TITLE);
  Game game(window);
  game.start();
  game.run();
  return 0;
}