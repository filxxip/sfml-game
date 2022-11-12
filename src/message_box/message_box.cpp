#include "message_box.h"
#include "../../data/config_file.h"

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
  if (components.keyboard.wasClickedYet(sf::Keyboard::Enter)) {
    components.keyboard.clickAndUnclickKey(sf::Keyboard::Enter);
    if (defaultIsInOptions()) {
      default_button->command();
    }
  }
}

void CustomMessageBox::checkEscape() {
  if (components.keyboard.wasClickedYet(sf::Keyboard::Escape)) {
    // components.keyboard.setClicked(sf::Keyboard::Escape);
    components.keyboard.clickAndUnclickKey(sf::Keyboard::Escape);
    destroy(); // a moze close
    // components.keyboard.clickAndUnclickKey(sf::Keyboard::Escape);
    // std::cout << "i tu" << std::endl;
    // components.keyboard.setNotClickedAfterDelay(sf::Keyboard::Escape);
    // }
  }
}

bool CustomMessageBox::defaultIsInOptions() {
  return default_button != nullptr;
}

CustomMessageBox::Ptr CustomMessageBox::create(MainGameComponents &components) {
  return std::make_shared<CustomMessageBox>(components);
}

const std::unordered_map<
    MsgBoxFactory::MessageBoxType,
    std::unordered_map<MsgBoxFactory::MsgBoxMapTypes, std::string>>
    MsgBoxFactory::factory_data{
        {MsgBoxFactory::MessageBoxType::APP_EXIT,
         {{MsgBoxFactory::MsgBoxMapTypes::TITLE, MessageBoxData::EXIT_TITLE},
          {MsgBoxFactory::MsgBoxMapTypes::CONTENT,
           MessageBoxData::EXIT_CONTENT},
          {MsgBoxFactory::MsgBoxMapTypes::RENDERER_MAIN, RendererNames::MSGBOX},
          {MsgBoxFactory::MsgBoxMapTypes::RENDERER_BUTTON,
           RendererNames::MSGBOX_BUTTON}}},
        {MsgBoxFactory::MessageBoxType::GAME_EXIT,
         {{MsgBoxFactory::MsgBoxMapTypes::TITLE,
           MessageBoxData::EXIT_GAME_TITLE},
          {MsgBoxFactory::MsgBoxMapTypes::CONTENT,
           MessageBoxData::EXIT_GAME_CONTENT},
          {MsgBoxFactory::MsgBoxMapTypes::RENDERER_MAIN, RendererNames::MSGBOX},
          {MsgBoxFactory::MsgBoxMapTypes::RENDERER_BUTTON,
           RendererNames::MSGBOX_BUTTON}}},
        {MsgBoxFactory::MessageBoxType::NEW_GAME,
         {{MsgBoxFactory::MsgBoxMapTypes::TITLE,
           MessageBoxData::NEW_GAME_TITLE},
          {MsgBoxFactory::MsgBoxMapTypes::CONTENT,
           MessageBoxData::NEW_GAME_CONTENT},
          {MsgBoxFactory::MsgBoxMapTypes::RENDERER_MAIN, RendererNames::MSGBOX},
          {MsgBoxFactory::MsgBoxMapTypes::RENDERER_BUTTON,
           RendererNames::MSGBOX_BUTTON}}}};

tgui::Theme MsgBoxFactory::theme = tgui::Theme(Paths::MESSAGE_BOX_STYLE);

CustomMessageBox::Ptr
MsgBoxFactory::createBase(MainGameComponents &components) {
  auto msgbox = CustomMessageBox::create(components);
  msgbox->setPositionLocked(true);
  msgbox->setSize(MessageBoxData::BASE_SIZE);
  msgbox->setTitleTextSize(MessageBoxData::TEXT_SIZE);
  msgbox->setLabelAlignment(tgui::MessageBox::Alignment::Center);
  PositionWidgetMenager::setMiddle(components.window, msgbox);
  return msgbox;
}

CustomMessageBox::Ptr MsgBoxFactory::create(MainGameComponents &components,
                                            MessageBoxType type) {
  auto msgbox = createBase(components);
  const auto &msgbox_data = factory_data.at(type);
  msgbox->setText(msgbox_data.at(MsgBoxFactory::MsgBoxMapTypes::CONTENT));
  msgbox->setTitle(msgbox_data.at(MsgBoxFactory::MsgBoxMapTypes::TITLE));
  msgbox->setRenderer(theme.getRenderer(
      msgbox_data.at(MsgBoxFactory::MsgBoxMapTypes::RENDERER_MAIN)));
  msgbox->getRenderer()->setButton(theme.getRenderer(
      msgbox_data.at(MsgBoxFactory::MsgBoxMapTypes::RENDERER_BUTTON)));
  return msgbox;
}

CustomMessageBox::Ptr MsgBoxFactory::createCustomMessageBox(
    MainGameComponents &components, MsgBoxFactory::MessageBoxType type,
    std::vector<std::pair<CustomMessageBox::Options, std::function<void()>>>
        buttons) {
  auto msgbox = MsgBoxFactory::create(components, type);
  // components.gui.add(msgbox);
  // menu.getLayout()->blockButtons();
  msgbox->addButtons(buttons);
  return msgbox;
  // active_messagebox = msgbox;
}