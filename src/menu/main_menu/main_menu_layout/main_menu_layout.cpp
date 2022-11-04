#include "main_menu_layout.h"

namespace {
std::unordered_map<EnumMenu::MainMenuOpts, std::string> main_menu_options_text{
    {EnumMenu::MainMenuOpts::EXIT, "exit game"},
    {EnumMenu::MainMenuOpts::LOAD, "load game"},
    {EnumMenu::MainMenuOpts::NEW, "new game"},
    {EnumMenu::MainMenuOpts::RESULTS, "see your results"},
};
}

MainMenuLayout::Ptr MainMenuLayout::create() {
  return std::make_shared<MainMenuLayout>();
}

void MainMenuLayout::addOption(EnumMenu::MainMenuOpts option, float space,
                               float ratio) {
  auto button = tgui::Button::create(main_menu_options_text.at(option));
  buttons.emplace(option, button);
  addWidget(button, space, ratio);
}

// void MainMenuLayout::addPicture(const std::string &path, float space, float
// ratio) {
//   auto renderer = title_picture->getRenderer();
//   auto texture = tgui::Texture(path);
//   renderer->setTexture(texture);
//   addWidget(title_picture, space, ratio);
// }

MainMenuLayout::MainMenuLayout() : Menu<EnumMenu::MainMenuOpts>() {
  setSize(400, 500);
}