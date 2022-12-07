#pragma once
#include <memory>

#include "../../../data/config_file.h"
#include "../../game/main_game_components/main_game_components.h"
#include "../../picture/game_picture.h"
#include "../bomb/fire.h"

class LiveItem : public TimeItem {
protected:
  int lives;

public:
  using Ptr = std::shared_ptr<LiveItem>;
  LiveItem(MainGameComponents &components_, const std::string &path,
           int initial_lives);
  int getRemainLives();
  void decreaseLives();
  void initializeEnd();
  bool isExpired(bool game_is_running);
};

class Stone : public LiveItem {
public:
  Stone(MainGameComponents &components_);
  static LiveItem::Ptr create(MainGameComponents &components_);
};

class Box : public LiveItem {
public:
  Box(MainGameComponents &components_);
  static LiveItem::Ptr create(MainGameComponents &components_);
};

class BoxFactory {
public:
  enum class Types { STONE, BOX };
  static GamePicture::Ptr create(MainGameComponents &components_, Types type);
};