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

template <typename T> class PartMenager {
  Range x_range;
  Range y_range;
  Range maximum_elements_x;
  Range maximum_elements_y;

protected:
  std::vector<T> box_vector;
  MainGameComponents &components;

public:
  // enum class PartsTypes {}

  PartMenager(MainGameComponents &components_, Range &&x_range_,
              Range &&y_range_);
  PartMenager(MainGameComponents &components_);
  bool canBeInSpace(const tgui::Layout2d &layout,
                    const tgui::Layout2d &size) const;
  bool containIndex(const Index &index) const;

  bool canBeInsideAnyItem(const tgui::Layout2d &layout,
                          const tgui::Layout2d &size) const;
  bool isWidgetInsideAnyItem(const tgui::Layout2d &layout,
                             const tgui::Layout2d &size) const;

  bool isPositionFree(const tgui::Layout2d &layout,
                      const tgui::Layout2d &size) const;
  void addItem(T item);

  void destroy();
  void checkExpired(bool game_is_running);
  void removeEveryExpiredItem(bool game_is_running);
  void checkAndRemoveExpiredItems(bool game_is_running);
};

class BoxesPartMenager : public PartMenager<LiveItem::Ptr> {
public:
  BoxesPartMenager(MainGameComponents &components_, Range &&x_range_,
                   Range &&y_range_)
      : PartMenager<LiveItem::Ptr>(components_, std::move(x_range_),
                                   std::move(y_range_)) {}

  void deacreaseIndexItemLive(const Index &index) {
    for (auto &box : box_vector) {
      if (box->getIndexPosition() == index) {
        box->decreaseLives();
      }
    }
  }
};

class BoxMenager {
private:
  PartMenager<Fire::Ptr> fire_menager;
  std::vector<BoxesPartMenager> menager_vector;

  MainGameComponents &components;
  Player &player;

  void inittializeBoxes(int count);
  void createEdges();
  void createBoard();
  void addItem(Index &&positions, LiveItem::Ptr &&item);

  void backendFireCreator(Index &&init_index, bool &condition,
                          std::vector<Index> &checked_vectors);

public:
  BoxMenager(MainGameComponents &components_, Player &player_);

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
  void checkBoxesExpired(bool game_is_running);
  void checkPlayerOnFire(const Index &index);
};