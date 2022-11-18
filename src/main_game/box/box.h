#pragma once

#include "../../game/main_game_components/main_game_components.h"
#include "../../picture/game_picture.h"

class Box {
public:
  Box(MainGameComponents &components_);

  void put(double position_x, double position_y);

  GamePicture::Ptr &getPicture();
  bool isWidgetInside(const tgui::Layout2d &layout,
                      const tgui::Layout2d &size) const;

private:
  MainGameComponents &components;
  GamePicture::Ptr picture;
};