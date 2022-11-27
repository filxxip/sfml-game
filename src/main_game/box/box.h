#pragma once
#include <memory>

#include "../../../data/config_file.h"
#include "../../game/main_game_components/main_game_components.h"
#include "../../picture/game_picture.h"

// class BoardItem : public GamePicture {
// public:
//   using Ptr = std::shared_ptr<BoardItem>;
//   BoardItem(MainGameComponents &components_);

//   static BoardItem::Ptr create(MainGameComponents &components) {
//     return std::make_shared<BoardItem>(components);
//   }
//   bool isWidgetInside(const tgui::Layout2d &layout,
//                       const tgui::Layout2d &size) const;
// };

// class

// class Box {
// public:
//   using Ptr = std::shared_ptr<Box>;

//   Box(MainGameComponents &components_, const std::string &path);

//   void put(double position_x, double position_y);

//   GamePicture::Ptr &getPicture();
//   bool isWidgetInside(const tgui::Layout2d &layout,
//                       const tgui::Layout2d &size) const;

//   static Ptr create(MainGameComponents &components_, const std::string &path)
//   {
//     return std::make_shared<Box>(components_, path);
//   }

// private:
//   MainGameComponents &components;
//   GamePicture::Ptr picture;
// };

// class Fire2 : public GamePicture {
//   Timer timer;

// public:
//   Fire(MainGameComponents &components);
//   using Ptr = std::shared_ptr<Fire>;
//   static Fire::Ptr create(MainGameComponents &components) {
//     return std::make_shared<Fire>(components);
//   }

//   void measure(bool game_is_running) { timer.measure(game_is_running); }
//   int getLasts() const { return timer.getLasts(); }

//   bool isExpired() const;

//   void execute();
// };

class Stone : public GamePicture {
public:
  Stone(MainGameComponents &components_)
      : GamePicture(components_, Paths::STONE) {
    setSize({BoxData::ScaleMenager::getBoxSize(),
             BoxData::ScaleMenager::getBoxSize()});
  }

  static GamePicture::Ptr create(MainGameComponents &components_) {
    return std::make_shared<Stone>(components_);
  }
};
class Box : public GamePicture {
public:
  Box(MainGameComponents &components_)
      : GamePicture(components_, Paths::BOX_PATH) {
    setSize({BoxData::ScaleMenager::getBoxSize(),
             BoxData::ScaleMenager::getBoxSize()});
  }
  static GamePicture::Ptr create(MainGameComponents &components_) {
    return std::make_shared<Box>(components_);
  }
};

class BoxFactory {
public:
  enum class Types { STONE, BOX };
  static GamePicture::Ptr create(MainGameComponents &components_, Types type) {
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
    return GamePicture::create(components_, path);
  }
};