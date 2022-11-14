#pragma once

#include "../../background/background.h"
#include "../custom_keyboard/custom_keyboard.h"

#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

struct MainGameComponents {
  sf::RenderWindow &window;
  tgui::Gui gui;
  CustomKeyboard keyboard;
  sf::Event evnt;
  Background background;

  MainGameComponents(sf::RenderWindow &window_);
  const bool isOpened() const;
  void setBackground(const std::string &texture_path);
  bool isClicked(sf::Keyboard::Key key);
  bool isReleased(sf::Keyboard::Key key);
  void start();
  void addOver(tgui::Widget::Ptr down_widget, tgui::Widget::Ptr up_widget);
};