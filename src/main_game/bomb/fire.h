#pragma once

#include "../../../data/config_file.h"
#include "../../game/main_game_components/main_game_components.h"
#include "../../picture/game_picture.h"
#include "../timer/timer.h"

class TimeItem : public GamePicture {
  Timer timer;

public:
  TimeItem(MainGameComponents &components, const std::string &path);
  using Ptr = std::shared_ptr<TimeItem>;
  static TimeItem::Ptr create(MainGameComponents &components,
                              const std::string &path) {
    return std::make_shared<TimeItem>(components, std::move(path));
  }

  void measure(bool game_is_running) { timer.measure(game_is_running); }
  int getLasts() const { return timer.getLasts(); }

  bool isExpired(bool game_is_running);
};

class Fire : public TimeItem {
public:
  Fire(MainGameComponents &components_) : TimeItem(components_, Paths::FIRE) {
    setSize({BoxData::ScaleMenager::getBoxSize(),
             BoxData::ScaleMenager::getBoxSize()});
  }

  static TimeItem::Ptr create(MainGameComponents &components) {
    return std::make_shared<Fire>(components);
  }
};

// class Fire : public GamePicture {
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