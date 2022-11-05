#include "message_box.h"
#include "../../data/config_file.h"

CustomMessageBox::CustomMessageBox(const sf::RenderWindow &window)
    : tgui::MessageBox(), ratio_data(window) {
  onSizeChange([this]() { ratio_data.setSizeRatios(getSize()); });
  onPositionChange([this]() { ratio_data.setPositionRatios(getPosition()); });
}

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
  MessageBoxButton msg_box_button{name, [this, command]() {
                                    command();
                                    destroy();
                                  }};
  buttons.push_back(std::move(msg_box_button));
  onButtonPress([this, &name](const auto &text) {
    if (text == name) {
      getCommand(name)();
      // destroy();
    }
  });
  tgui::MessageBox::addButton(name);
}

void CustomMessageBox::addButton(Options option,
                                 std::function<void()> command) {
  addButton(options_names.at(option), command);
}

CustomMessageBox::Ptr CustomMessageBox::create(const sf::RenderWindow &window) {
  return std::make_shared<CustomMessageBox>(window);
}

const RatioWidgetData &CustomMessageBox::getRatioData() const {
  return ratio_data;
}
void CustomMessageBox::setRatioData() {
  ratio_data.set(getSize(), getPosition());
}

tgui::Theme MsgBoxFactory::theme = tgui::Theme(Paths::MESSAGE_BOX_STYLE);

CustomMessageBox::Ptr
MsgBoxFactory::createBase(const sf::RenderWindow &window) {
  auto msgbox = CustomMessageBox::create(window);
  msgbox->setPositionLocked(true);
  msgbox->setSize(MessageBoxData::BASE_SIZE);
  msgbox->setTitleTextSize(MessageBoxData::TEXT_SIZE);
  msgbox->setLabelAlignment(tgui::MessageBox::Alignment::Center);
  PositionWidgetMenager::setMiddle(window, msgbox);
  return msgbox;
}

CustomMessageBox::Ptr MsgBoxFactory::create(const sf::RenderWindow &window) {
  auto msgbox = createBase(window);
  msgbox->setText(MessageBoxData::EXIT_CONTENT);
  msgbox->setTitle(MessageBoxData::EXIT_TITLE);
  msgbox->setRenderer(theme.getRenderer(RendererNames::MSGBOX));
  msgbox->getRenderer()->setButton(
      theme.getRenderer(RendererNames::MSGBOX_BUTTON));
  return msgbox;
}