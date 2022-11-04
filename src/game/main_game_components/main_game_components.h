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

  MainGameComponents(sf::RenderWindow &window_);
  const bool isOpened() const;
  void start();
};