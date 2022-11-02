#pragma once

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
  void addButton(const std::string &name, std::function<void()> command);
  void addButton(Options option, std::function<void()> command);
  decltype(auto) getCommand(const std::string &name);
  decltype(auto) getButtonItr(const std::string &name);
  void setMiddle(const sf::RenderWindow &window);

protected:
  std::vector<MessageBoxButton> buttons;
};

class ExitStayMessageBox : public CustomMessageBox {
public:
  using Ptr = std::shared_ptr<ExitStayMessageBox>;
  ExitStayMessageBox(const sf::RenderWindow &window);
  static Ptr create(const sf::RenderWindow &window);

private:
  tgui::Theme theme;
};
