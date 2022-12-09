#include "message_box.h"
#include "../../data/config_file.h"
#include <fstream>

const std::unordered_map<CustomMessageBox::Options, std::string>
    CustomMessageBox::options_names{
        {CustomMessageBox::Options::STAY, "stay"},
        {CustomMessageBox::Options::RESUME, "resume"},
        {CustomMessageBox::Options::EXIT, "exit"},
        {CustomMessageBox::Options::YES, "yes"},
        {CustomMessageBox::Options::NO, "no"}};
CustomMessageBox::CustomMessageBox(MainGameComponents &components_)
    : components(components_), default_button(nullptr), tgui::MessageBox() {
  buttons.reserve(10);
  // onSizeChange([this]() { ratio_data.setSizeRatios(getSize()); });
  // onPositionChange([this]() { ratio_data.setPositionRatios(getPosition());
  // });
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
                                 std::function<void()> command,
                                 bool default_button_) {
  MessageBoxButton msg_box_button{name, [this, command]() {
                                    command();
                                    close();
                                  }};
  buttons.push_back(std::move(msg_box_button));
  if (default_button_) {
    default_button = &buttons.at(buttons.size() - 1);
  }
  onButtonPress([this, &name](const auto &text) {
    if (text == name) {
      getCommand(name)();
    }
  });
  tgui::MessageBox::addButton(name);
}

void CustomMessageBox::addButtons(
    std::vector<std::pair<Options, std::function<void()>>> buttons) {
  if (buttons.size() > 0) {
    auto &&[option, function] = std::move(buttons.at(0));
    addButton(option, std::move(function), true);
  }
  std::for_each(buttons.begin() + 1, buttons.end(), [this](auto &button) {
    auto &&[option, function] = std::move(button);
    addButton(option, std::move(function), false);
  });
}

void CustomMessageBox::addButton(Options option, std::function<void()> command,
                                 bool default_button_) {
  addButton(options_names.at(option), command, default_button_);
}

void CustomMessageBox::checkEnter() {
  if (components.isClicked(sf::Keyboard::Enter)) {
    // components.keyboard.clickAndUnclickKey(sf::Keyboard::Enter);
    if (defaultIsInOptions()) {
      default_button->command();
    }
  }
}

void CustomMessageBox::checkEscape() {
  if (message_box_escape_key && components.isClicked(sf::Keyboard::Escape) &&
      components.keyboard.isNotClicked(sf::Keyboard::Escape)) {
    destroy(); // a moze close
  }
}

bool CustomMessageBox::defaultIsInOptions() {
  return default_button != nullptr;
}

CustomMessageBox::Ptr CustomMessageBox::create(MainGameComponents &components) {
  return std::make_shared<CustomMessageBox>(components);
}

tgui::Theme MsgBoxFactory::theme = tgui::Theme(Paths::MESSAGE_BOX_STYLE);

CustomMessageBox::Ptr
MsgBoxFactory::createCustomMessageBox(MainGameComponents &components,
                                      nlohmann::json json_file) {
  auto msgbox = CustomMessageBox::create(components);
  msgbox->setPositionLocked(true);
  msgbox->setSize(json_file.at(JsonNames::SIZE_WIDTH_).get<int>(),
                  json_file.at(JsonNames::SIZE_HEIGHT).get<int>());
  msgbox->setTitleTextSize(json_file.at("text_size").get<int>());
  msgbox->setLabelAlignment(tgui::MessageBox::Alignment::Center);
  PositionWidgetMenager::setMiddle(components.window, msgbox);
  msgbox->setText(json_file.at(JsonNames::CONTENT).get<std::string>());
  msgbox->setTitle(json_file.at(JsonNames::TITLE).get<std::string>());
  msgbox->setRenderer(theme.getRenderer(
      json_file.at(JsonNames::MSGBOX_NAME).get<std::string>()));
  msgbox->getRenderer()->setButton(theme.getRenderer(
      json_file.at(JsonNames::MSGBOX_BUTTON_NAME).get<std::string>()));
  return msgbox;
}

CustomMessageBox::Ptr MsgBoxFactory::createCustomMessageBox(
    MainGameComponents &components, nlohmann::json json_file,
    std::vector<std::pair<CustomMessageBox::Options, std::function<void()>>>
        buttons) {
  auto msgbox = MsgBoxFactory::createCustomMessageBox(components, json_file);
  msgbox->addButtons(buttons);
  return msgbox;
}

CustomMessageBox::Ptr MsgBoxFactory::create(MainGameComponents &components,
                                            const std::string &file_path) {
  return createCustomMessageBox(components, getJson(file_path));
}
CustomMessageBox::Ptr MsgBoxFactory::create(
    MainGameComponents &components, const std::string &file_path,
    std::vector<std::pair<CustomMessageBox::Options, std::function<void()>>>
        buttons) {
  return createCustomMessageBox(components, getJson(file_path), buttons);
}

nlohmann::json MsgBoxFactory::getJson(const std::string &path) {
  std::fstream f(path);
  nlohmann::json data = nlohmann::json::parse(std::move(f));
  return data;
}