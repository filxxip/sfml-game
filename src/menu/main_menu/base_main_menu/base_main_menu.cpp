#include "base_main_menu.h"
#include "../../../../data/config_file.h"

MainMenu::MainMenu(MainGameComponents &components_, const std::string &path)
    : components(components_),
      main_menu_layout(MainMenuLayout::create(components)),
      title_picture(CustomPicture::create(components.window, path)) {}

void MainMenu::setMiddle() {
  PositionWidgetMenager::setMiddle(
      components.window, title_picture,
      {MainMenuData::PICTURE_X_MOVEMENT, MainMenuData::PICTURE_Y_MOVEMENT});
  PositionWidgetMenager::setMiddle(
      components.window, main_menu_layout,
      {MainMenuData::LAYOUT_X_MOVEMENT, MainMenuData::LAYOUT_Y_MOVEMENT});
}

void MainMenu::createCustomMessageBox(
    const std::string &path,
    std::vector<std::pair<CustomMessageBox::Options, std::function<void()>>>
        buttons) {
  auto msgbox = MsgBoxFactory::create(components, path, buttons);
  components.gui.add(msgbox);
  main_menu_layout->blockButtons();
  active_messagebox = msgbox;
}

void MainMenu::checkMsgBox() {
  if (active_messagebox->expired()) {
    main_menu_layout->setOptionUsingKeyBoard();
  } else {
    active_messagebox.checkKeyboard();
    if (active_messagebox->expired()) {
      main_menu_layout->unblockButtons();
    }
  }
}

void MainMenu::initialize() {
  components.background.setImage(Paths::TEXTURE_PATH);
  std::cout << components.gui.getWidgets().size() << std::endl;
  components.gui.add(main_menu_layout);
  components.gui.add(title_picture);
  main_menu_layout->unblockButtons();
  std::cout << components.gui.getWidgets().size() << std::endl;
}
void MainMenu::remove() {
  components.gui.remove(main_menu_layout);
  components.gui.remove(title_picture);
  // components.background.setImage(Paths::TEXTURE_PATH);
}

const bool MainMenu::isInitialized() const {
  const auto &widgets = components.gui.getWidgets();
  auto index = std::find(widgets.begin(), widgets.end(), main_menu_layout);
  auto index2 = std::find(widgets.begin(), widgets.end(), title_picture);
  return index != widgets.end() && index2 != widgets.end();
}

const CustomPicture::Ptr &MainMenu::getPicture() const { return title_picture; }
const MainMenuLayout::Ptr &MainMenu::getLayout() const {
  return main_menu_layout;
}

// void MainMenu::setVisible(bool status) {
//   main_menu_layout->setVisible(status);
//   title_picture->setVisible(status);
// }

void MainMenu::addButtonCommand(EnumMenu::MainMenuOpts option,
                                std::function<void()> command) {
  getLayout()->addButtonCommand(option, std::move(command));
}

void MainMenu::addToGui(tgui::Gui &gui) {
  gui.add(main_menu_layout);
  gui.add(title_picture);
}

MainMenu MainMenuFactory::create(MainGameComponents &components_) {
  auto menu = MainMenu(components_, Paths::BOMBER_TITLE_PATH);
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

  menu.setMiddle();
  return menu;
}
