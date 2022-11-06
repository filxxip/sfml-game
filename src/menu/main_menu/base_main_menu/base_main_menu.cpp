#include "base_main_menu.h"
#include "../../../../data/config_file.h"

MainMenu::MainMenu(const sf::RenderWindow &window_, const std::string &path)
    : main_menu_layout(MainMenuLayout::create(window_)),
      title_picture(CustomPicture::create(window_, path)) {}

void MainMenu::setMiddle(const sf::RenderWindow &window) {
  PositionWidgetMenager::setMiddle(
      window, title_picture,
      {MainMenuData::PICTURE_X_MOVEMENT, MainMenuData::PICTURE_Y_MOVEMENT});
  PositionWidgetMenager::setMiddle(
      window, main_menu_layout,
      {MainMenuData::LAYOUT_X_MOVEMENT, MainMenuData::LAYOUT_Y_MOVEMENT});
}

CustomPicture::Ptr MainMenu::getPicture() const { return title_picture; }
MainMenuLayout::Ptr MainMenu::getLayout() const { return main_menu_layout; }

void MainMenu::setVisible(bool status) {
  main_menu_layout->setVisible(status);
  title_picture->setVisible(status);
}

void MainMenu::addButtonCommand(EnumMenu::MainMenuOpts option,
                                std::function<void()> command) {
  getLayout()->addButtonCommand(option, std::move(command));
}

MainMenu MainMenuFactory::create(const sf::RenderWindow &window) {
  auto menu = MainMenu(window, Paths::BOMBER_TITLE_PATH);
  menu.getPicture()->setSize(MainMenuData::PICTURE_SIZE);
  menu.getLayout()->setSize(MainMenuData::LAYOUT_SIZE);
  menu.getLayout()->addOption(EnumMenu::MainMenuOpts::NEW,
                              MainMenuData::FREE_SPACE_RATIO,
                              MainMenuData::BUTTON_RATIO);
  menu.getLayout()->addOption(EnumMenu::MainMenuOpts::LOAD,
                              MainMenuData::FREE_SPACE_RATIO,
                              MainMenuData::BUTTON_RATIO);
  menu.getLayout()->addOption(EnumMenu::MainMenuOpts::RESULTS,
                              MainMenuData::FREE_SPACE_RATIO,
                              MainMenuData::BUTTON_RATIO);
  menu.getLayout()->addOption(EnumMenu::MainMenuOpts::OPTIONS,
                              MainMenuData::FREE_SPACE_RATIO,
                              MainMenuData::BUTTON_RATIO);
  menu.getLayout()->addOption(EnumMenu::MainMenuOpts::EXIT,
                              MainMenuData::FREE_SPACE_RATIO,
                              MainMenuData::BUTTON_RATIO);
  menu.setMiddle(window);
  menu.getLayout()->setButtonRender(RendererNames::BUTTON);
  // menu.getLayout()->setLayoutRender(RendererNames::LAYOUT);
  return menu;
}