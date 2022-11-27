#pragma once

#include "../../game/main_game_components/main_game_components.h"
#include "../../main_game/bomb/fire.h"
#include "../../picture/picture.h"
#include "../player/player.h"
#include "data_classes.h"

#include "box.h"
#include <TGUI/Widget.hpp>
#include <string>
#include <utility>
class PartMenager {
  Range x_range;
  Range y_range;
  Range maximum_elements_x;
  Range maximum_elements_y;

protected:
  std::vector<GamePicture::Ptr> box_vector;
  MainGameComponents &components;

public:
  // enum class PartsTypes {}

  PartMenager(MainGameComponents &components_, Range &&x_range_,
              Range &&y_range_);
  PartMenager(MainGameComponents &components_);
  bool canBeInSpace(const tgui::Layout2d &layout,
                    const tgui::Layout2d &size) const;

  bool canBeInsideAnyItem(const tgui::Layout2d &layout,
                          const tgui::Layout2d &size) const;
  bool isWidgetInsideAnyItem(const tgui::Layout2d &layout,
                             const tgui::Layout2d &size) const;

  bool isPositionFree(const tgui::Layout2d &layout,
                      const tgui::Layout2d &size) const;
  void addItem(GamePicture::Ptr item);

  void destroy();
  void checkExpired(bool game_is_running);
  void removeEveryExpiredItem(bool game_is_running);
};

// class FireMenager : public PartMenager {

//   public:
//   void createWholeFire(Index &&init_index, int bomb_power);
//   void checkFiresExpired(bool game_is_running);
// };

// class FireMenager : public PartMenager {
// public:
//   void checkFiresExpired(bool game_is_running);
//   void removeEveryExpiredFire();
// };

// class BoxMenagerPart {
// public:
//   Range x_range;
//   Range y_range;
//   Range maximum_elements_x;
//   Range maximum_elements_y;

//   std::vector<Box::Ptr> box_vector;
//   // std::vector<Fire::Ptr> fire_vector;

// public:
//   BoxMenagerPart(Range &&x_range_, Range &&y_range_);
//   bool canBeInSpace(const tgui::Layout2d &layout,
//                     const tgui::Layout2d &size) const;

//   bool canBeInsideAnyBox(const tgui::Layout2d &layout,
//                          const tgui::Layout2d &size) const;
//   bool isWidgetInsideAnyBox(const tgui::Layout2d &layout,
//                             const tgui::Layout2d &size) const;
//   void addBox(Box::Ptr box);
//   // void

//   void destroy(MainGameComponents &components_);
// };

class BoxMenager {
private:
  PartMenager fire_menager;
  std::vector<PartMenager> menager_vector;

  MainGameComponents &components;
  const Player &player;

  void inittializeBoxes(int count);
  void createEdges();
  void createBoard();
  void addItem(Index &&positions, GamePicture::Ptr &&item);

  void backendFireCreator(Index &&init_index, bool &condition);

public:
  BoxMenager(MainGameComponents &components_, const Player &player_);

  void addBox(Index &&indexes);
  void addStone(Index &&indexes);
  void addFire(Index &&indexes);

  void initialize();
  bool isPositionFree(const tgui::Layout2d &layout,
                      const tgui::Layout2d &size) const;
  bool isFromFirePositionFree(const tgui::Layout2d &layout,
                              const tgui::Layout2d &size) const;
  bool isEntirePositionFree(const tgui::Layout2d &layout,
                            const tgui::Layout2d &size) const;
  bool isPositionFree(const tgui::Layout2d &layout) const;
  bool areIndexesFree(const Index &indexes) const;

  void remove();

  void createWholeFire(Index &&init_index, int bomb_power);
  void checkFiresExpired(bool game_is_running);
};