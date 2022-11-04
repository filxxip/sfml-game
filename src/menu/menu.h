#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/Backend/Renderer/BackendRenderTarget.hpp>
#include <TGUI/Widget.hpp>
#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/VerticalLayout.hpp>

#include <functional>

namespace EnumMenu {
enum class MainMenuOpts { NEW, LOAD, RESULTS, EXIT };
enum class MidGameOpts { LOAD, SAVE };
} // namespace EnumMenu

template <typename OPT_ENUM> class Menu : public tgui::VerticalLayout {
public:
  using Ptr = std::shared_ptr<Menu<OPT_ENUM>>;

  Menu();

  virtual void addOption(OPT_ENUM option, float space, float ratio) = 0;

  void setMiddle(const sf::RenderWindow &window);
  decltype(auto) getButtonCommand(OPT_ENUM option);
  void addButtonCommand(OPT_ENUM option, std::function<void()> command);
  void draw(const sf::RenderWindow &window);

  void setWidgetSpace(const tgui::Widget::Ptr &widget, float ratio);
  void addWidget(const tgui::Widget::Ptr &widget, float space, float ratio);

  void setButtonRender(const std::string &object_name);
  void setLayoutRender(const std::string &object_name);

protected:
  std::map<OPT_ENUM, tgui::Button::Ptr> buttons;
  std::map<OPT_ENUM, std::function<void()>> buttons_functions;
  tgui::Theme theme;

private:
  bool is_middled = false;

  const double getXRatio(const sf::RenderWindow &window) const;
  const double getYRatio(const sf::RenderWindow &window) const;
};
