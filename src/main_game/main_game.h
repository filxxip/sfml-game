#pragma once

#include "../game/main_game_components/main_game_components.h"
#include "../message_box/message_box.h"
#include "box/box_menager.h"
#include "down_panel/down_panel.h"
#include "player/player.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class MainGame {
public:
  enum class State { RUNNING, PAUSE };

  MainGame(MainGameComponents &components_);
  void initialize();
  void remove();
  const bool isInitialized() const;
  const Player &getPlayer() const;

  void movePlayer();
  void checkPause();
  void createExitMessageBox();
  void createPauseMessageBox();

  const bool isRunning() const;
  const bool isPause() const;

  void movePlayerIfValidNewPosition(Player::Movement movement);

  void doPlayerActivities();
  void checkBombs();

private:
  MainGameComponents &components;
  State state = State::RUNNING;
  Player player;
  DownPanel panel;
  BoxMenager box_menager;

public:
  tgui::Signal own_signal;
  tgui::Label customwidget;
  UniqueWindowMsgBox active_messagebox;
};