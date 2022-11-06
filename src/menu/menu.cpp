#include "menu.h"
#include "../../data/config_file.h"

template <typename OPT_ENUM>
Menu<OPT_ENUM>::Menu(const sf::RenderWindow &window)
    : theme(Paths::MENU_STYLE), ratio_data(window), VerticalLayout() {
  setSize("100%", "100%");
  onSizeChange([this]() { ratio_data.setSizeRatios(getSize()); });
  onPositionChange([this]() { ratio_data.setPositionRatios(getPosition()); });
}

template <typename OPT_ENUM>
void Menu<OPT_ENUM>::addButtonCommand(OPT_ENUM option,
                                      std::function<void()> command) {
  buttons.at(option)->onMousePress(std::move(command));
}

template <typename OPT_ENUM>
void Menu<OPT_ENUM>::setWidgetSpace(const tgui::Widget::Ptr &widget,
                                    float ratio) {
  auto index = getWidgetIndex(widget);
  std::cout << index << std::endl;
  setRatio(index, ratio);
}

template <typename OPT_ENUM>
void Menu<OPT_ENUM>::addWidget(const tgui::Widget::Ptr &widget, float space,
                               float ratio) {
  add(widget);
  addSpace(space);
  setWidgetSpace(widget, ratio);
}

template <typename OPT_ENUM>
void Menu<OPT_ENUM>::setButtonRender(const std::string &object_name) {
  for (auto [id, button] : buttons) {
    button->setRenderer(theme.getRenderer(object_name));
  }
}
template <typename OPT_ENUM>
void Menu<OPT_ENUM>::setLayoutRender(const std::string &object_name) {
  setRenderer(theme.getRenderer(object_name));
}

template <typename OPT_ENUM>
const RatioWidgetData &Menu<OPT_ENUM>::getRatioData() const {
  return ratio_data;
}

template <typename OPT_ENUM> void Menu<OPT_ENUM>::setRatioData() {
  ratio_data.set(getSize(), getPosition());
}

template <typename OPT_ENUM> void Menu<OPT_ENUM>::blockButtons() {
  auto button = tgui::Button::create();
  for (auto &[name, button] : buttons) {
    button->setEnabled(false);
  }
}
template <typename OPT_ENUM> void Menu<OPT_ENUM>::unblockButtons() {
  auto button = tgui::Button::create();
  for (auto &[name, button] : buttons) {
    button->setEnabled(true);
  }
}

template class Menu<EnumMenu::MainMenuOpts>;