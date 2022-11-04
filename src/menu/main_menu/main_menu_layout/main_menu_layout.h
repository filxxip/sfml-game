#pragma once

#include "../../menu.h"

class MainMenuLayout : public Menu<EnumMenu::MainMenuOpts> {
public:
  using Ptr = std::shared_ptr<MainMenuLayout>;
  MainMenuLayout(const sf::RenderWindow &window);
  static Ptr create(const sf::RenderWindow &window);
  void addOption(EnumMenu::MainMenuOpts option, float space, float ratio);
};