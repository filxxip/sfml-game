#pragma once

#include "../../menu.h"

class MainMenuLayout : public Menu<EnumMenu::MainMenuOpts> {
public:
  using Ptr = std::shared_ptr<MainMenuLayout>;
  MainMenuLayout();
  static Ptr create();
  void addOption(EnumMenu::MainMenuOpts option, float space, float ratio);
  // void addPicture(const std::string &path, float space, float ratio);

private:
  // tgui::Picture::Ptr title_picture;
};