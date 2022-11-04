#include "main_menu_layout.h"

namespace {
std::unordered_map<EnumMenu::MainMenuOpts, std::string> main_menu_options_text{
    {EnumMenu::MainMenuOpts::EXIT, "exit game"},
    {EnumMenu::MainMenuOpts::LOAD, "load game"},
    {EnumMenu::MainMenuOpts::NEW, "new game"},
    {EnumMenu::MainMenuOpts::RESULTS, "see your results"},
};
}

MainMenuLayout::Ptr MainMenuLayout::create(const sf::RenderWindow &window) {
  return std::make_shared<MainMenuLayout>(window);
}

void MainMenuLayout::addOption(EnumMenu::MainMenuOpts option, float space,
                               float ratio) {
  auto button = tgui::Button::create(main_menu_options_text.at(option));
  buttons.emplace(option, button);
  addWidget(button, space, ratio);
}

MainMenuLayout::MainMenuLayout(const sf::RenderWindow &window)
    : Menu<EnumMenu::MainMenuOpts>(window) {
  setSize(400, 500);
}