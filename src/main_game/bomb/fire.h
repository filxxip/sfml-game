#pragma once

#include "../../../data/config_file.h"
#include "../../game/main_game_components/main_game_components.h"
#include "../../picture/game_picture.h"
#include "../timer/timer.h"

class TimeItem : public GamePicture {
protected:
  Timer timer;
  double item_live_time = 0;

public:
  TimeItem(MainGameComponents &components, const std::string &path);
  using Ptr = std::shared_ptr<TimeItem>;
  static TimeItem::Ptr create(MainGameComponents &components,
                              const std::string &path) {
    return std::make_shared<TimeItem>(components, std::move(path));
  }
  void setLiveTime(double value) { item_live_time = value; }
  void measure(bool game_is_running) { timer.measure(game_is_running); }
  int getLasts() const { return timer.getLasts(); }

  bool isExpired(bool game_is_running);
};

class Fire : public TimeItem {
public:
  Fire(MainGameComponents &components_) : TimeItem(components_, Paths::FIRE) {
    timer.run();
    setSize({BoxData::ScaleMenager::getBoxSize(),
             BoxData::ScaleMenager::getBoxSize()});
  }

  static TimeItem::Ptr create(MainGameComponents &components) {
    auto fire = std::make_shared<Fire>(components);
    fire->setLiveTime(BombData::FIRE_ACTIVE_TIME);
    return fire;
  }
};
