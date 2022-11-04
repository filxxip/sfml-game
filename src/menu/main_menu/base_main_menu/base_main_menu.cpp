#include "base_main_menu.h"

MainMenu::MainMenu(const std::string &path)
    : main_menu_layout(MainMenuLayout::create()),
      title_picture(CustomPicture::create(path)) {
  //   setPicture(path);
  //   title_picture->setPosition(100, 100);
}

// void MainMenu::setPictureMiddle(const sf::RenderWindow &window) {
//   const auto [window_width, window_height] = window.getSize();
//   const auto [picture_width, picture_height] = title_picture->getSize();
//   title_picture->setPosition((window_width - picture_width) / 2,
//                              (window_height - picture_height) / 2);
// }

void MainMenu::setMiddle(const sf::RenderWindow &window) {
  main_menu_layout->setMiddle(window);
  title_picture->setMiddle(window);
}

// void MainMenu::setPicture(const std::string &path) {
//   auto renderer = title_picture->getRenderer();
//   auto texture = tgui::Texture(path);
//   renderer->setTexture(texture);
// }

CustomPicture::Ptr MainMenu::getPicture() const { return title_picture; }
MainMenuLayout::Ptr MainMenu::getLayout() const { return main_menu_layout; }

void MainMenu::setVisible(bool status) {
  main_menu_layout->setVisible(status);
  title_picture->setVisible(status);
}

MainMenu MainMenuFactory::create(const sf::RenderWindow &window) {
  auto menu = MainMenu("/home/filip/Documents/sfml-game/images/bomber.png");
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