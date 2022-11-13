#pragma once

#include "../../data/config_file.h"
#include "../game/main_game_components/main_game_components.h"
#include "../position_widget_menager/position_widget_menager.h"

#include <SFML/Graphics.hpp>
#include <TGUI/Loading/Theme.hpp>
#include <TGUI/Widgets/MessageBox.hpp>
#include <nlohmann/json.hpp>

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
  static CustomMessageBox::Ptr create(MainGameComponents &components,
                                      const std::string &file_path);
  static CustomMessageBox::Ptr create(
      MainGameComponents &components, const std::string &file_path,
      std::vector<std::pair<CustomMessageBox::Options, std::function<void()>>>
          buttons);

private:
  static CustomMessageBox::Ptr
  createCustomMessageBox(MainGameComponents &components,
                         nlohmann::json json_file);
  static CustomMessageBox::Ptr createCustomMessageBox(
      MainGameComponents &components, nlohmann::json json_file,
      std::vector<std::pair<CustomMessageBox::Options, std::function<void()>>>
          buttons);

  static nlohmann::json getJson(const std::string &path);

  static tgui::Theme theme;
};
