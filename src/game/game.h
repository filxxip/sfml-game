#pragma once

#include "../menu/main_menu/base_main_menu/base_main_menu.h"
#include "../message_box/message_box.h"
#include "../position_widget_menager/position_widget_menager.h"
#include "main_game_components/main_game_components.h"

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
  void poolEvents();
  CustomMessageBox::Ptr createMessageBox();
  void createExitMessageBox();
  // void createPauseMessageBox();
  // const bool isOpened() const;
  // const bool isRunning() const;
  // const bool isPause() const;

private:
  MainGameComponents components;
  Background background;
  MainMenu menu;
  std::weak_ptr<CustomMessageBox> active_messagebox;

  // State state = State::RUNNING;
};
