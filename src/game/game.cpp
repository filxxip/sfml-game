
#include "game.h"

Game::Game(sf::RenderWindow &window_) : window(window_) {}

void Game::start() {
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(60);
}