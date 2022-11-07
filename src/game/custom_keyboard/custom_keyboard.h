#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/Widgets/Label.hpp>

class CustomKeyboard {
private:
  std::map<sf::Keyboard::Key, bool> clickedStatus;
  void setClickedWithThreadDelay(sf::Keyboard::Key key, const int miliseconds);
  void setNotClickedWithThreadDelay(sf::Keyboard::Key key,
                                    const int miliseconds);

public:
  CustomKeyboard();
  const bool isClicked(sf::Keyboard::Key key) const;
  const bool isNotClicked(sf::Keyboard::Key key) const;
  void setClicked(sf::Keyboard::Key key);
  void setClickedAfterDelay(sf::Keyboard::Key key);
  void setNotClicked(sf::Keyboard::Key key);
  void setNotClickedAfterDelay(sf::Keyboard::Key key);
};