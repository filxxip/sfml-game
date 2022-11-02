#include "src/game/game.h"
#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window;
  Game game(window);
  game.start();
  game.run();
  // window.setVerticalSyncEnabled(true);
  // // window.setFramerateLimit(60);
  // sf::Texture texture;
  // texture.loadFromFile("/home/filip/Documents/sfml-game/texture.jpg");

  // sf::View view(sf::Vector2f(50, 50), sf::Vector2f(100, 100));
  // window.setView(view);

  // sf::VertexArray triangle(sf::Triangles, 3);
  // triangle[0].position = sf::Vector2f(10, 10);
  // triangle[1].position = sf::Vector2f(100, 10);
  // triangle[2].position = sf::Vector2f(100, 100);
  // triangle[0].color = sf::Color::Green;
  // triangle[1].color = sf::Color::Blue;
  // triangle[2].color = sf::Color::Yellow;

  // sf::Sprite sprite;
  // sprite.setTexture(texture);
  // while (window.isOpen()) {
  //   sf::Event evnt;
  //   while (window.pollEvent(evnt)) {
  //     if (evnt.type == sf::Event::Closed) {
  //       window.close();
  //     }
  //     if (evnt.type == sf::Event::GainedFocus) {
  //       std::cout << "hello back" << std::endl;
  //     }
  //     if (evnt.type == sf::Event::LostFocus) {
  //       std::cout << "meh" << std::endl;
  //     }
  //   }

  //   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
  //     if (view.getCenter().x > 50 && view.getCenter().x > 50) {
  //       view.move(-2, -2);
  //     }
  //   }
  //   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
  //     view.move(-2, -2);
  //   }
  //   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
  //     window.setPosition(
  //         sf::Vector2i(window.getPosition().x, window.getPosition().y + 1));
  //   }
  //   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
  //     window.setPosition(
  //         sf::Vector2i(window.getPosition().x, window.getPosition().y - 1));
  //   }

  //   if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
  //     triangle[1].color = sf::Color::Yellow;
  //     triangle[2].color = sf::Color::Blue;
  //   }
  //   if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
  //     triangle[1].color = sf::Color::Blue;
  //     triangle[2].color = sf::Color::Yellow;
  //   }
  //   window.clear();
  //   window.setView(view);
  //   window.draw(sprite);
  //   window.draw(triangle);
  //   window.display();
  // }
  return 0;
}