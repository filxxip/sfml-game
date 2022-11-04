#pragma once

#include "../menu.h"
#include <TGUI/AllWidgets.hpp>
// class MainMenuLayout : public Menu<EnumMenu::MainMenuOpts> {
// public:
//   using Ptr = std::shared_ptr<MainMenuLayout>;
//   MainMenuLayout();
//   static Ptr create();
//   void addOption(EnumMenu::MainMenuOpts option, float space, float ratio);
//   // void addPicture(const std::string &path, float space, float ratio);

// private:
//   // tgui::Picture::Ptr title_picture;
// };

// class MainMenu {
// public:
//   MainMenu(const std::string &path);
//   tgui::Picture::Ptr getPicture() const;
//   MainMenuLayout::Ptr getLayout() const;
//   void setPicture(const std::string &path);
//   void setMiddle(const sf::RenderWindow &window);

// private:
//   void setPictureMiddle(const sf::RenderWindow &window);

//   MainMenuLayout::Ptr main_menu_layout;
//   tgui::Picture::Ptr title_picture;
// };

// class MainMenuFactory {
// public:
//   static MainMenu create(const sf::RenderWindow &window);
// };