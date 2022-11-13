#include "menu.h"
#include "../../data/config_file.h"
#include <iterator>

template <typename OPT_ENUM>
Menu<OPT_ENUM>::Menu(MainGameComponents &components_)
    : components(components_), theme(Paths::MENU_STYLE),
      current_option(buttons.end()),
      default_theme_button_name(RendererNames::DEFAULT_BUTTON),
      active_theme_button_name(RendererNames::ACTIVE_BUTTON), VerticalLayout() {
  setSize("100%", "100%");
  // onSizeChange([this]() {
  //   std::cout << "zmieniam wielkosc" << std::endl;
  //   ratio_data.setSizeRatios(getSize());
  // });
  // onPositionChange([this]() { ratio_data.setPositionRatios(getPosition());
  // });
}

template <typename OPT_ENUM>
void Menu<OPT_ENUM>::addButtonCommand(OPT_ENUM option,
                                      std::function<void()> command) {
  auto button_pair =
      std::find_if(buttons.begin(), buttons.end(),
                   [option](auto &pair) { return pair.first == option; });

  if (button_pair != buttons.end()) {
    buttons_functions.at(option) = std::move(command);
    button_pair->second->onMousePress(buttons_functions.at(option));
  }
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
bool Menu<OPT_ENUM>::isCurrentOptionInButtons() const {
  return current_option < buttons.end() && current_option >= buttons.begin();
}

template <typename OPT_ENUM>
void Menu<OPT_ENUM>::setCurrentTheme(const std::string &theme_name) {
  setWidgetTheme(theme_name, current_option->second);
}

template <typename OPT_ENUM>
void Menu<OPT_ENUM>::setWidgetTheme(const std::string &theme_name,
                                    tgui::Widget::Ptr widget) {
  widget->setRenderer(theme.getRenderer(theme_name));
}

template <typename OPT_ENUM>
void Menu<OPT_ENUM>::setCurrentOption(const tgui::Button::Ptr &button) {
  current_option =
      std::find_if(buttons.begin(), buttons.end(), [&button](const auto &pair) {
        return pair.second == button;
      });
}

template <typename OPT_ENUM> void Menu<OPT_ENUM>::unsetCurrentOption() {
  // setCurrentTheme(default_theme_button_name);
  current_option = buttons.end();
}

template <typename OPT_ENUM> void Menu<OPT_ENUM>::resetThemes() {
  for (auto &button : buttons) {
    setWidgetTheme(default_theme_button_name, button.second);
  }
  if (isCurrentOptionInButtons()) {
    setCurrentTheme(active_theme_button_name);
  }
}

template <typename OPT_ENUM>
void Menu<OPT_ENUM>::setDefaultThemeName(const std::string &name) {
  default_theme_button_name = name;
  resetThemes();
}

template <typename OPT_ENUM>
void Menu<OPT_ENUM>::setActiveThemeName(const std::string &name) {
  active_theme_button_name = name;
  resetThemes();
}

template <typename OPT_ENUM>
void Menu<OPT_ENUM>::addButton(const tgui::Button::Ptr &button, float space,
                               float ratio) {
  addWidget(button, space, ratio);
  button->setRenderer(theme.getRenderer(default_theme_button_name));
  button->onMouseEnter([this, button]() {
    if (isCurrentOptionInButtons()) {
      setCurrentTheme(default_theme_button_name);
    }
    setWidgetTheme(active_theme_button_name, button);
    setCurrentOption(button);
  });
  button->onMouseLeave([this, button]() {
    setWidgetTheme(default_theme_button_name, button);
    if (isCurrent(button)) {
      unsetCurrentOption();
    }
  });
}

template <typename OPT_ENUM>
bool Menu<OPT_ENUM>::isCurrent(const tgui::Button::Ptr &button) const {

  return std::find_if(buttons.begin(), buttons.end(),
                      [&button](const auto &pair) {
                        return pair.second == button;
                      }) == current_option;
}

template <typename OPT_ENUM>
void Menu<OPT_ENUM>::setLayoutRender(const std::string &object_name) {
  setRenderer(theme.getRenderer(object_name));
}

// template <typename OPT_ENUM>
// const RatioWidgetData &Menu<OPT_ENUM>::getRatioData() const {
//   return ratio_data;
// }

// template <typename OPT_ENUM> void Menu<OPT_ENUM>::setRatioData() {
//   ratio_data.set(getSize(), getPosition());
// }

template <typename OPT_ENUM> void Menu<OPT_ENUM>::moveMenu() {
  if (components.isClicked(sf::Keyboard::Down)) {
    std::cout << "hello" << std::endl;
    focuseNextButton();
    // components.keyboard.clickAndUnclickKey(sf::Keyboard::Down);
  }
  if (components.isClicked(sf::Keyboard::Up)) {
    focusePreviousButton();
    // components.keyboard.clickAndUnclickKey(sf::Keyboard::Up);
  }
}

template <typename OPT_ENUM> void Menu<OPT_ENUM>::setOptionUsingKeyBoard() {
  if (components.isClicked(sf::Keyboard::Enter) && isCurrentOptionInButtons()) {

    buttons_functions.at(current_option->first)();
    // components.keyboard.clickAndUnclickKey(sf::Keyboard::Enter);
  }
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

template <typename OPT_ENUM> void Menu<OPT_ENUM>::focuseNextButton() {
  if (!isCurrentOptionInButtons()) {
    auto optional_current = buttons.begin();
    if (optional_current->second->isEnabled()) {
      setWidgetTheme(active_theme_button_name, optional_current->second);
      current_option = optional_current;
    }
    return;
  }

  auto optional_current = current_option == std::prev(buttons.end())
                              ? buttons.begin()
                              : std::next(current_option);
  if (optional_current->second->isEnabled()) {
    setCurrentTheme(default_theme_button_name);
    setWidgetTheme(active_theme_button_name, optional_current->second);
    current_option = optional_current;
  }
}

template <typename OPT_ENUM> void Menu<OPT_ENUM>::focusePreviousButton() {
  if (!isCurrentOptionInButtons()) {
    auto optional_current = std::prev(buttons.end());
    if (optional_current->second->isEnabled()) {
      setWidgetTheme(active_theme_button_name, optional_current->second);
      current_option = optional_current;
    }
    return;
  }
  auto optional_current = current_option == buttons.begin()
                              ? std::prev(buttons.end())
                              : std::prev(current_option);
  if (optional_current->second->isEnabled()) {
    setCurrentTheme(default_theme_button_name);
    setWidgetTheme(active_theme_button_name, optional_current->second);
    current_option = optional_current;
  }
} // cos pozmieniac bo podobne

template class Menu<EnumMenu::MainMenuOpts>;