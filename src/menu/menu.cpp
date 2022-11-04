#include "menu.h"

template <typename OPT_ENUM>
Menu<OPT_ENUM>::Menu()
    : theme("/home/filip/Documents/sfml-game/themes/menu.style"),
      VerticalLayout() {
  setSize("100%", "100%");
}

template <typename OPT_ENUM>
void Menu<OPT_ENUM>::setMiddle(const sf::RenderWindow &window) {
  is_middled = true;
  const auto [window_width, window_height] = window.getSize();
  std::cout << window_width << std::endl;
  std::cout << window_height << std::endl;
  const auto [menu_width, menu_height] = getSize();
  setPosition((window_width - menu_width) / 2,
              (window_height - menu_height) / 2);
  std::cout << getPosition().x << std::endl;
}

template <typename OPT_ENUM>
void Menu<OPT_ENUM>::draw(const sf::RenderWindow &window) {
  if (is_middled) {
    setMiddle(window);
  }
}

template <typename OPT_ENUM>
decltype(auto) Menu<OPT_ENUM>::getButtonCommand(OPT_ENUM option) {
  return buttons_functions.at(option);
}

template <typename OPT_ENUM>
void Menu<OPT_ENUM>::addButtonCommand(OPT_ENUM option,
                                      std::function<void()> command) {
  buttons_functions.at(option) = command;
}

template <typename OPT_ENUM>
void Menu<OPT_ENUM>::setWidgetSpace(const tgui::Widget::Ptr &widget,
                                    float ratio) {
  auto index = getWidgetIndex(widget);
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
    // button->setWidth(100);
  }
}
template <typename OPT_ENUM>
void Menu<OPT_ENUM>::setLayoutRender(const std::string &object_name) {
  setRenderer(theme.getRenderer(object_name));
}

template <typename OPT_ENUM>
const double Menu<OPT_ENUM>::getXRatio(const sf::RenderWindow &window) const {
  return static_cast<double>(getSize().x) / window.getSize().x;
}

template <typename OPT_ENUM>
const double Menu<OPT_ENUM>::getYRatio(const sf::RenderWindow &window) const {
  return static_cast<double>(getSize().y) / window.getSize().y;
}

template class Menu<EnumMenu::MainMenuOpts>;