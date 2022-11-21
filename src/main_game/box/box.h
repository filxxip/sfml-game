#pragma once
#include <memory>

#include "../../../data/config_file.h"
#include "../../game/main_game_components/main_game_components.h"
#include "../../picture/game_picture.h"

class Box {
public:
  using Ptr = std::shared_ptr<Box>;

  Box(MainGameComponents &components_, const std::string &path);

  void put(double position_x, double position_y);

  GamePicture::Ptr &getPicture();
  bool isWidgetInside(const tgui::Layout2d &layout,
                      const tgui::Layout2d &size) const;

  static Ptr create(MainGameComponents &components_, const std::string &path) {
    return std::make_shared<Box>(components_, path);
  }

private:
  MainGameComponents &components;
  GamePicture::Ptr picture;
};

class BoxFactory {
public:
  enum class Types { STONE, BOX };
  static Box::Ptr create(MainGameComponents &components_, Types type) {
    std::string path;
    switch (type) {
    case Types::BOX: {
      path = Paths::BOX_PATH;
      break;
    }
    case Types::STONE: {
      path = Paths::STONE;
      break;
    }
    }
    return Box::create(components_, path);
  }
};