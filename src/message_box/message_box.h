#pragma once

#include "../../data/config_file.h"
#include "../game/main_game_components/main_game_components.h"
#include "../position_widget_menager/position_widget_menager.h"

#include <SFML/Graphics.hpp>
#include <TGUI/Loading/Theme.hpp>
#include <TGUI/Widgets/MessageBox.hpp>

struct MessageBoxButton {
  std::string name;
  std::function<void()> command;
};

class CustomMessageBox : public tgui::MessageBox {
protected:
  // RatioWidgetData ratio_data;
  std::vector<MessageBoxButton> buttons;

public:
  using Ptr = std::shared_ptr<CustomMessageBox>;
  enum class Options { STAY, EXIT, YES, NO, RESUME };
  static const std::unordered_map<Options, std::string> options_names;

  CustomMessageBox(MainGameComponents &components_);
  void addButton(
      Options option, std::function<void()> command = []() {},
      bool default_button_ = false);
  void
  addButtons(std::vector<std::pair<Options, std::function<void()>>> buttons);
  decltype(auto) getCommand(const std::string &name);
  decltype(auto) getButtonItr(const std::string &name);

  void checkEnter();
  void checkEscape();
  bool defaultIsInOptions();

  static Ptr create(MainGameComponents &components);

private:
  MainGameComponents &components;
  MessageBoxButton *default_button;
  void addButton(const std::string &name, std::function<void()> command,
                 bool default_button_ = false);
};

class UniqueWindowMsgBox {
protected:
  std::weak_ptr<CustomMessageBox> active_messagebox;

public:
  void destroy() {
    if (!active_messagebox.expired()) {
      active_messagebox.lock()->destroy();
      active_messagebox.reset();
    }
  }

  void checkKeyboard() {
    if (!active_messagebox.expired()) {
      active_messagebox.lock()->checkEnter();
    }
    if (!active_messagebox.expired()) {
      active_messagebox.lock()->checkEscape();
    }
  }

  // private:
  //   void checkEnter() { active_messagebox.lock()->checkEnter(); }
  //   void checkEscape() { active_messagebox.lock()->checkEscape(); }

public:
  std::weak_ptr<CustomMessageBox> *operator->() { return &active_messagebox; }

  decltype(auto) operator=(std::shared_ptr<CustomMessageBox> ptr) {
    active_messagebox = std::move(ptr);
    // active_messagebox.lock()->onClose([this]() { destroy(); });
    return *this;
  }
};

class MsgBoxFactory {
public:
  enum class MessageBoxType { APP_EXIT, GAME_EXIT, NEW_GAME, RESUME_GAME };
  static CustomMessageBox::Ptr create(MainGameComponents &components,
                                      MessageBoxType type);
  static CustomMessageBox::Ptr createCustomMessageBox(
      MainGameComponents &components, MessageBoxType type,
      std::vector<std::pair<CustomMessageBox::Options, std::function<void()>>>
          buttons);

private:
  enum class MsgBoxMapTypes { TITLE, CONTENT, RENDERER_MAIN, RENDERER_BUTTON };

  static const std::unordered_map<
      MessageBoxType, std::unordered_map<MsgBoxMapTypes, std::string>>
      factory_data;

  static tgui::Theme theme;
  static CustomMessageBox::Ptr createBase(MainGameComponents &components,
                                          MessageBoxType type);
};
