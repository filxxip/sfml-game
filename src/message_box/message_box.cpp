#include "message_box.h"

decltype(auto) CustomMessageBox::getButtonItr(const std::string &name) {
  auto result = std::find_if(buttons.begin(), buttons.end(),
                             [&name](const auto &custom_button) {
                               return custom_button.name == name;
                             });
  return result;
}

decltype(auto) CustomMessageBox::getCommand(const std::string &name) {
  auto button_itr = getButtonItr(name);
  if (button_itr != buttons.end()) {
    return button_itr->command;
  }
  std::function<void()> empty_func = []() {};
  return empty_func;
}

void CustomMessageBox::addButton(const std::string &name,
                                 std::function<void()> command) {
  MessageBoxButton msg_box_button{name, command};
  buttons.push_back(std::move(msg_box_button));
  onButtonPress([this, &name](const auto &text) {
    if (text == name) {
      getCommand(name)();
    }
  });
  tgui::MessageBox::addButton(name);
}

void CustomMessageBox::setMiddle(const sf::RenderWindow &window) {
  const auto [width, height] = window.getSize();
  const auto [message_width, message_height] = getSize();
  setPosition((width - message_width) / 2, (height - message_height) / 2);
}

void CustomMessageBox::addButton(Options option,
                                 std::function<void()> command) {
  addButton(options_names.at(option), command);
}

ExitStayMessageBox::ExitStayMessageBox(const sf::RenderWindow &window)
    : theme("../themes/messagebox.style") {
  setText("Are you sure the exit this game?");
  // getRenderer().gettit
  // setPositionLocked(true);
  setSize(250, 110);
  setMiddle(window);
  setTitleTextSize(18);
  // getRenderer()->setTitleBarHeight
  setTitle("Exit Game");
  setRenderer(theme.getRenderer("ExitMessageBoxRendererData"));
  setLabelAlignment(tgui::MessageBox::Alignment::Center);
  tgui::RendererData data;
  // setTitleButtons(1);
  // getRenderer().
  // getRenderer()->setTitleBarColor
}

ExitStayMessageBox::Ptr
ExitStayMessageBox::create(const sf::RenderWindow &window) {
  return std::make_shared<ExitStayMessageBox>(window);
}