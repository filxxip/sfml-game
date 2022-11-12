#pragma once

#include "../../../game/main_game_components/main_game_components.h"
#include "../../../message_box/message_box.h"
#include "../../../picture/picture.h"
#include "../main_menu_layout/main_menu_layout.h"

#include <TGUI/Backend/SFML-Graphics.hpp>

#include <TGUI/Widgets/Picture.hpp>

class MainMenu {
public:
  MainMenu(MainGameComponents &components_, const std::string &path);
  const CustomPicture::Ptr &getPicture() const;
  const MainMenuLayout::Ptr &getLayout() const;
  // void setVisible(bool status);
  void initialize();
  void remove();
  const bool isInitialized() const;
  void setMiddle();

  void addButtonCommand(EnumMenu::MainMenuOpts option,
                        std::function<void()> command);
  void addToGui(tgui::Gui &gui);
  void createCustomMessageBox(
      MsgBoxFactory::MessageBoxType type,
      std::vector<std::pair<CustomMessageBox::Options, std::function<void()>>>
          buttons);

  void checkMsgBox();

private:
  MainGameComponents &components;
  MainMenuLayout::Ptr main_menu_layout;
  CustomPicture::Ptr title_picture;
  UniqueWindowMsgBox active_messagebox;
};

class MainMenuFactory {
public:
  static MainMenu create(MainGameComponents &components_);
};