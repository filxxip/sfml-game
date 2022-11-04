#include "main_menu.h"
#include <TGUI/Texture.hpp>

// namespace {
// std::unordered_map<EnumMenu::MainMenuOpts, std::string>
// main_menu_options_text{
//     {EnumMenu::MainMenuOpts::EXIT, "exit game"},
//     {EnumMenu::MainMenuOpts::LOAD, "load game"},
//     {EnumMenu::MainMenuOpts::NEW, "new game"},
//     {EnumMenu::MainMenuOpts::RESULTS, "see your results"},
// };
// }

// MainMenuLayout::Ptr MainMenuLayout::create() {
//   return std::make_shared<MainMenuLayout>();
// }

// void MainMenuLayout::addOption(EnumMenu::MainMenuOpts option, float space,
//                                float ratio) {
//   auto button = tgui::Button::create(main_menu_options_text.at(option));
//   buttons.emplace(option, button);
//   addWidget(button, space, ratio);
// }

// // void MainMenuLayout::addPicture(const std::string &path, float space,
// float
// // ratio) {
// //   auto renderer = title_picture->getRenderer();
// //   auto texture = tgui::Texture(path);
// //   renderer->setTexture(texture);
// //   addWidget(title_picture, space, ratio);
// // }

// MainMenuLayout::MainMenuLayout() : Menu<EnumMenu::MainMenuOpts>() {
//   setSize(400, 500);
// }

// MainMenu::MainMenu(const std::string &path)
//     : main_menu_layout(MainMenuLayout::create()),
//       title_picture(tgui::Picture::create()) {
//   setPicture(path);
//   title_picture->setPosition(100, 100);
// }

// void MainMenu::setPictureMiddle(const sf::RenderWindow &window) {
//   const auto [window_width, window_height] = window.getSize();
//   const auto [picture_width, picture_height] = title_picture->getSize();
//   title_picture->setPosition((window_width - picture_width) / 2,
//                              (window_height - picture_height) / 2);
// }

// void MainMenu::setMiddle(const sf::RenderWindow &window) {
//   main_menu_layout->setMiddle(window);
//   setPictureMiddle(window);
// }

// void MainMenu::setPicture(const std::string &path) {
//   auto renderer = title_picture->getRenderer();
//   auto texture = tgui::Texture(path);
//   renderer->setTexture(texture);
// }

// tgui::Picture::Ptr MainMenu::getPicture() const { return title_picture; }
// MainMenuLayout::Ptr MainMenu::getLayout() const { return main_menu_layout; }

// MainMenu MainMenuFactory::create(const sf::RenderWindow &window) {
//   auto menu = MainMenu("/home/filip/Documents/sfml-game/images/bomber.png");
//   // menu->addPicture("/home/filip/Documents/sfml-game/images/bomber.png", 4,
//   // 10);
//   menu.getLayout()->addOption(EnumMenu::MainMenuOpts::NEW, 2, 5);
//   menu.getLayout()->addOption(EnumMenu::MainMenuOpts::LOAD, 2, 5);
//   menu.getLayout()->addOption(EnumMenu::MainMenuOpts::RESULTS, 2, 5);
//   menu.getLayout()->addOption(EnumMenu::MainMenuOpts::EXIT, 2, 5);
//   menu.setMiddle(window);
//   menu.getLayout()->setButtonRender("Button");
//   menu.getLayout()->setLayoutRender("Layout");
//   return menu;
// }