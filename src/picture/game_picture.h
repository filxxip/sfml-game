#pragma once
#include "../game/main_game_components/main_game_components.h"
#include "../main_game/box/data_classes.h"
#include "picture.h"
// #include "../main_game/player/player.h"

class GamePicture : public CustomPicture {
protected:
  MainGameComponents &components;

public:
  using Ptr = std::shared_ptr<GamePicture>;
  GamePicture(MainGameComponents &components_, const std::string &path);
  static Ptr create(MainGameComponents &components_, const std::string &path);

  bool isWidgetInside(const tgui::Layout2d &position,
                      const tgui::Layout2d &size) const;

  void setIndexPosition(Index &&index);
  Index getIndexPosition();
  virtual bool isExpired(bool game_is_running) { return false; }
};

class BonusItem : public GamePicture {
public:
  enum class Type {
    CLICK_BOMB,//bomb type
    MYSTERY_BOMB,//bomb type
    NEW_BOMB,
    HEART_BOMB,//bomb type
    NEW_HEART,//panel changer
    PLUS_SPEED,//player
    PLUS_POWER,//player
    PLUS_TWO_POWER,//player
    REMOVE_RANDOM_OPP
  };
  static const std::unordered_map<Type, std::string> types_paths;

public:
  using Ptr = std::shared_ptr<BonusItem>;
  BonusItem(MainGameComponents &components_, Type type_);
  static Ptr create(MainGameComponents &components_, Type type_) {
    std::cout<<types_paths.size()<<std::endl;
    return std::make_shared<BonusItem>(components_, type_);
  }

  Type getType() const { return type; }

  virtual void execute(){
    own_signal.emit(&signal_label);
  }
  void connectSignal(std::function<void()> function){
    own_signal.connect(function);
  }

private:
tgui::Signal own_signal;
tgui::Label signal_label;
  Type type;

};