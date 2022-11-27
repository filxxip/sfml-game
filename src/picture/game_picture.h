#pragma once
#include "../game/main_game_components/main_game_components.h"
#include "../main_game/box/data_classes.h"
#include "picture.h"

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
