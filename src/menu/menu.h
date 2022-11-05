#pragma once

#include "../position_widget_menager/position_widget_menager.h"

#include <SFML/Graphics.hpp>
#include <TGUI/Backend/Renderer/BackendRenderTarget.hpp>
#include <TGUI/Widget.hpp>
#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/VerticalLayout.hpp>

#include <functional>

namespace EnumMenu {
enum class MainMenuOpts { NEW, LOAD, RESULTS, EXIT, OPTIONS };
enum class MidGameOpts { LOAD, SAVE };
} // namespace EnumMenu

template <typename OPT_ENUM> class Menu : public tgui::VerticalLayout {
public:
  using Ptr = std::shared_ptr<Menu<OPT_ENUM>>;

  Menu(const sf::RenderWindow &window);

  virtual void addOption(OPT_ENUM option, float space, float ratio) = 0;

  decltype(auto) getButtonCommand(OPT_ENUM option);
  void addButtonCommand(
      OPT_ENUM option,
      std::function<void()>
          command); // wprowadzic albo dziedziczenie wielokrotno albo myslec

  void setWidgetSpace(const tgui::Widget::Ptr &widget, float ratio);
  void addWidget(const tgui::Widget::Ptr &widget, float space, float ratio);

  void setButtonRender(const std::string &object_name);
  void setLayoutRender(const std::string &object_name);

  const RatioWidgetData &getRatioData() const;
  void setRatioData();

protected:
  std::map<OPT_ENUM, tgui::Button::Ptr> buttons;
  std::map<OPT_ENUM, std::function<void()>> buttons_functions;
  tgui::Theme theme;
  RatioWidgetData ratio_data;
};
