#include "main_menu_layout.h"
#include "../../../../data/config_file.h"

namespace {
std::unordered_map<EnumMenu::MainMenuOpts, std::string> main_menu_options_text{
    {EnumMenu::MainMenuOpts::EXIT, MainMenuData::ButtonsText::EXIT},
    {EnumMenu::MainMenuOpts::LOAD, MainMenuData::ButtonsText::LOAD},
    {EnumMenu::MainMenuOpts::NEW, MainMenuData::ButtonsText::NEW},
    {EnumMenu::MainMenuOpts::RESULTS, MainMenuData::ButtonsText::RESULT},
    {EnumMenu::MainMenuOpts::OPTIONS, MainMenuData::ButtonsText::OPTIONS},
};
}

MainMenuLayout::Ptr MainMenuLayout::create(MainGameComponents &components) {
  return std::make_shared<MainMenuLayout>(components);
}

void MainMenuLayout::addOption(EnumMenu::MainMenuOpts option, float space,
                               float ratio) {
  if (std::find_if(buttons.begin(), buttons.end(), [option](auto &pair) {
        return pair.first == option;
      }) == buttons.end()) {
    auto button = tgui::Button::create(main_menu_options_text.at(option));
    buttons.push_back({option, button});
    buttons_functions.emplace(std::make_pair(option, []() {}));
    Menu::addButton(button, space, ratio);
  }
}

MainMenuLayout::MainMenuLayout(MainGameComponents &components)
    : Menu<EnumMenu::MainMenuOpts>(components) {}