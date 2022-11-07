#pragma once

#include "../position_widget_menager/position_widget_menager.h"

#include <SFML/Graphics.hpp>
#include <TGUI/Backend/Renderer/BackendRenderTarget.hpp>
#include <TGUI/Widget.hpp>
#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/VerticalLayout.hpp>

#include <functional>

namespace EnumMenu {
enum class MainMenuOpts { LOAD, NEW, RESULTS, OPTIONS, EXIT };
enum class MidGameOpts { LOAD, SAVE };
} // namespace EnumMenu

template <typename OPT_ENUM> class Menu : public tgui::VerticalLayout {
public:
  using Ptr = std::shared_ptr<Menu<OPT_ENUM>>;

  Menu(const sf::RenderWindow &window);

  virtual void addOption(OPT_ENUM option, float space, float ratio) = 0;

  void addButtonCommand(OPT_ENUM option, std::function<void()> command);

  void setWidgetSpace(const tgui::Widget::Ptr &widget, float ratio);
  void addWidget(const tgui::Widget::Ptr &widget, float space, float ratio);
  void addButton(const tgui::Button::Ptr &button, float space, float ratio);
  // void setButtonRender(const std::string &object_name);
  void setLayoutRender(const std::string &object_name);

  const RatioWidgetData &getRatioData() const;
  void setRatioData();

  void blockButtons();
  void unblockButtons();
  void focuseNextButton();
  void focusePreviousButton();

  void setDefaultThemeName(const std::string &name);
  void setActiveThemeName(const std::string &name);
  void resetThemes();

private:
  bool isCurrentOptionInButtons() const;
  void setCurrentTheme(const std::string &theme_name);
  void setWidgetTheme(const std::string &theme_name, tgui::Widget::Ptr widget);
  void setCurrentOption(const tgui::Button::Ptr &button);
  void unsetCurrentOption();

protected:
  std::vector<std::pair<OPT_ENUM, tgui::Button::Ptr>> buttons;
  tgui::Theme theme;
  RatioWidgetData ratio_data;
  decltype(buttons.end()) current_option;
  // OPT_ENUM current;

  std::string active_theme_button_name;
  std::string default_theme_button_name;
};
