#pragma once

#include "../../game/main_game_components/main_game_components.h"
#include "../../picture/picture.h"
#include "../player/player.h"
#include "data_classes.h"

#include "box.h"
#include <TGUI/Widget.hpp>
#include <string>
#include <utility>

class BoxMenagerPart {
public:
  Range x_range;
  Range y_range;
  Range maximum_elements_x;
  Range maximum_elements_y;

  std::vector<Box::Ptr> box_vector;

public:
  BoxMenagerPart(Range &&x_range_, Range &&y_range_);
  bool canBeInSpace(const tgui::Layout2d &layout,
                    const tgui::Layout2d &size) const;

  bool canBeInsideAnyBox(const tgui::Layout2d &layout,
                         const tgui::Layout2d &size) const;
  bool isWidgetInsideAnyBox(const tgui::Layout2d &layout,
                            const tgui::Layout2d &size) const;
  void addBox(Box::Ptr box);

  void destroy(MainGameComponents &components_);
};

class BoxMenager {
private:
  std::vector<BoxMenagerPart> menager_vector;
  MainGameComponents &components;
  const Player &player;

  void inittializeBoxes(int count);
  void createEdges();
  void addBox(Index &&positions, BoxFactory::Types type);

public:
  BoxMenager(MainGameComponents &components_, const Player &player_);
  void addBox(Index &&indexes);
  void addStone(Index &&indexes);
  void initialize();
  bool isPositionFree(const tgui::Layout2d &layout,
                      const tgui::Layout2d &size) const;
  bool isPositionFree(const tgui::Layout2d &layout) const;

  bool areIndexesFree(Index &&indexes) const;
  void remove();

  void createBoard();
};