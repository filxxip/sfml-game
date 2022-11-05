#pragma once

#include "../../data/config_file.h"
#include "../position_widget_menager/position_widget_menager.h"

#include <SFML/Graphics.hpp>
#include <TGUI/Loading/Theme.hpp>
#include <TGUI/Widgets/MessageBox.hpp>

struct MessageBoxButton {
  std::string name;
  std::function<void()> command;
};

class CustomMessageBox : public tgui::MessageBox {
public:
  using Ptr = std::shared_ptr<CustomMessageBox>;
  enum class Options { STAY, EXIT };
  std::map<Options, std::string> options_names{{Options::STAY, "stay"},
                                               {Options::EXIT, "exit"}};

  CustomMessageBox(const sf::RenderWindow &window);
  void addButton(
      Options option, std::function<void()> command = []() {});
  decltype(auto) getCommand(const std::string &name);
  decltype(auto) getButtonItr(const std::string &name);

  const RatioWidgetData &getRatioData() const;
  void setRatioData();

  static Ptr create(const sf::RenderWindow &window);

protected:
  RatioWidgetData ratio_data;
  std::vector<MessageBoxButton> buttons;

private:
  void addButton(const std::string &name, std::function<void()> command);
};

class MsgBoxFactory {
private:
  static tgui::Theme theme;

  static CustomMessageBox::Ptr createBase(const sf::RenderWindow &window);

public:
  static CustomMessageBox::Ptr create(const sf::RenderWindow &window);
};
