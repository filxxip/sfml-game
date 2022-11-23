#pragma once

#include "../../game/main_game_components/main_game_components.h"
#include "../../picture/picture.h"
#include "../player/player.h"

#include "box.h"
#include <TGUI/Widget.hpp>
#include <string>
#include <utility>

class Range {
private:
  double max;
  double min;

public:
  Range(double min_, double max_) : max(max_), min(min_) {}
  double getMax() const { return max; }
  void setMax(double new_max) { max = new_max; }
  double getMin() const { return min; }
  void setMin(double new_min) { min = new_min; }
  std::string toString() {
    return "range: (" + std::to_string(min) + " , " + std::to_string(max);
  }
};

class Index {
private:
  int x;
  int y;

public:
  Index(int x_, int y_) : x(x_), y(y_) {}
  tgui::Layout2d convertToPosition() const {
    return tgui::Layout2d(x * BoxData::INDEX_BOX_WIDTH +
                              0.5 * (BoxData::INDEX_BOX_WIDTH - BoxData::SIZE),
                          y * BoxData::INDEX_BOX_HEIGHT +
                              0.5 *
                                  (BoxData::INDEX_BOX_HEIGHT - BoxData::SIZE));
  }
  bool isValid() const {
    if (x > 0 && x < BoxData::MAX_X_INDEX) {
      if (y > 0 && y < BoxData::MAX_Y_INDEX) {
        return true;
      }
    }
    return false;
  }

  int getX() const { return x; }
  int getY() const { return y; }
};

class BoxMenagerPart {
public:
  Range x_range;
  Range y_range;
  Range maximum_elements_x;
  Range maximum_elements_y;

  std::vector<Box::Ptr> box_vector;

public:
  BoxMenagerPart(Range &&x_range_, Range &&y_range_);
  // bool canBeInSpace(const CustomPicture::Ptr &picture) const;
  bool canBeInSpace(const tgui::Layout2d &layout,
                    const tgui::Layout2d &size) const;

  bool canBeInsideAnyBox(const tgui::Layout2d &layout,
                         const tgui::Layout2d &size) const;
  bool isWidgetInsideAnyBox(const tgui::Layout2d &layout,
                            const tgui::Layout2d &size) const;
  void addBox(Box::Ptr box);
};

class BoxMenager {
private:
  std::vector<BoxMenagerPart> menager_vector;

  // double box_size;
  // std::pair<double, double> box_element_size; // box increased by its break
  MainGameComponents &components;
  const Player &player;
  // std::pair<int, int> max_indexes;

  void inittializeBoxes(int count);
  void createEdges();
  // void createBoxesData();
  void addBox(Index &&positions,
              BoxFactory::Types type); // dodawanie na index i wtedy na srodek,
                                       // metoda ktora zwraca index w zaleznosci
                                       // od wielkosci indeksa i pozycji
  // std::pair<int, int> getMaxXIndexes() const;
  // std::pair<int, int> getMaxYIndexes() const;
  // void addBoxItem(double position_x, double position_y);
  // void addStoneItem(double position_x, double position_y);
  // bool areIndexesValid(Index indexes) const;

public:
  BoxMenager(MainGameComponents &components_, const Player &player_);
  // void addBox(double position_x, double position_y);
  void addBox(Index &&indexes);
  void addStone(Index &&indexes);
  void initialize();
  bool isPositionFree(const tgui::Layout2d &layout,
                      const tgui::Layout2d &size) const;
  bool isPositionFree(const tgui::Layout2d &layout) const;
  bool areIndexesFree(Index &&indexes) const;
  // bool areIndexesFree(Index &&indexes, const tgui::Layout2d &size) const;

  void createBoard();
};