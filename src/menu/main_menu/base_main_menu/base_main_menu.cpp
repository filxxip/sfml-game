#include "base_main_menu.h"

MainMenu::MainMenu(const sf::RenderWindow &window_, const std::string &path)
    : main_menu_layout(MainMenuLayout::create(window_)),
      title_picture(CustomPicture::create(window_, path)) {}

void MainMenu::setMiddle(const sf::RenderWindow &window) {
  PositionWidgetMenager::setMiddle(window, title_picture, {0, -200});
  PositionWidgetMenager::setMiddle(window, main_menu_layout, {0, 100});
}

CustomPicture::Ptr MainMenu::getPicture() const { return title_picture; }
MainMenuLayout::Ptr MainMenu::getLayout() const { return main_menu_layout; }

void MainMenu::setVisible(bool status) {
  main_menu_layout->setVisible(status);
  title_picture->setVisible(status);
}

MainMenu MainMenuFactory::create(const sf::RenderWindow &window) {
  auto menu =
      MainMenu(window, "/home/filip/Documents/sfml-game/images/bomber.png");
  // menu->addPicture("/home/filip/Documents/sfml-game/images/bomber.png", 4,
  // 10);
  menu.getLayout()->addOption(EnumMenu::MainMenuOpts::NEW, 2, 5);
  menu.getLayout()->addOption(EnumMenu::MainMenuOpts::LOAD, 2, 5);
  menu.getLayout()->addOption(EnumMenu::MainMenuOpts::RESULTS, 2, 5);
  menu.getLayout()->addOption(EnumMenu::MainMenuOpts::EXIT, 2, 5);
  menu.setMiddle(window);
  menu.getLayout()->setButtonRender("Button");
  menu.getLayout()->setLayoutRender("Layout");
  return menu;
}