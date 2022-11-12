#pragma once

#include "../../menu.h"

class MainMenuLayout : public Menu<EnumMenu::MainMenuOpts> {
public:
  using Ptr = std::shared_ptr<MainMenuLayout>;
  MainMenuLayout(MainGameComponents &components);
  static Ptr create(MainGameComponents &components);
  void addOption(EnumMenu::MainMenuOpts option, float space, float ratio);
  // void unfocusButtons();
};