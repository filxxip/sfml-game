#pragma once

#include "../background/background.h"

#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/Widgets/Label.hpp>

class Game {
public:
  enum class State { PAUSE, RUNNING };

  Game(sf::RenderWindow &window_);
  void start();
  void setBackground(const std::string &texture_path);
  void run();
  void draw();
  void update();
  void createPauseMessageBox();
  const bool isOpened() const;
  const bool isRunning() const;
  const bool isPause() const;

private:
  sf::RenderWindow &window;
  tgui::Gui gui;
  Background background;
  sf::Event evnt;
  State state = State::RUNNING;
  void poolEvents();
};