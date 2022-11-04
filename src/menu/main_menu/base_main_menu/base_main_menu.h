#pragma once

#include "../../../picture/picture.h"
#include "../main_menu_layout/main_menu_layout.h"

#include <TGUI/Widgets/Picture.hpp>

class MainMenu {
public:
  MainMenu() = default;
  MainMenu(const sf::RenderWindow &window_, const std::string &path);
  CustomPicture::Ptr getPicture() const;
  MainMenuLayout::Ptr getLayout() const;
  void setVisible(bool status);
  void setMiddle(const sf::RenderWindow &window);

private:
  MainMenuLayout::Ptr main_menu_layout;
  CustomPicture::Ptr title_picture;
};

class MainMenuFactory {
public:
  static MainMenu create(const sf::RenderWindow &window);
};