#pragma once

#include "../../game/main_game_components/main_game_components.h"
#include "../../picture/picture.h"
#include "box.h"
#include <TGUI/Widget.hpp>
#include <string>
#include <utility>

class Range {
private:
  double max;
  double min;

public:
  Range(double min_, double max_) : max(max_), min(min_) {
    std::cout << toString() << std::endl;
  }
  double getMax() const { return max; }
  void setMax(double new_max) { max = new_max; }
  double getMin() const { return min; }
  void setMin(double new_min) { min = new_min; }
  std::string toString() {
    return "range: (" + std::to_string(min) + " , " + std::to_string(max);
  }
};

class BoxMenagerPart {
public:
  Range x_range;
  Range y_range;
  Range maximum_elements_x;
  Range maximum_elements_y;

  std::vector<Box::Ptr> box_vector;

public:
  enum class Measure { X, Y };
  BoxMenagerPart(Range &&x_range_, Range &&y_range_);
  bool canBeInSpace(const CustomPicture::Ptr &picture) const;
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

  double box_size;
  std::pair<double, double> box_element_size; // box increased by its break
  std::pair<int, int> max_indexes;

  void inittializeBoxes(int count);
  MainGameComponents &components;
  void createEdges();
  void createBoxesData();
  void addBox(tgui::Layout2d &&positions, BoxFactory::Types type);
  // void addBoxItem(double position_x, double position_y);
  // void addStoneItem(double position_x, double position_y);

public:
  BoxMenager(MainGameComponents &components_);
  // void addBox(double position_x, double position_y);
  void addBox(tgui::Layout2d &&indexes);
  void addStone(tgui::Layout2d &&indexes);
  void initialize();
  bool isPositionFree(const tgui::Layout2d &layout,
                      const tgui::Layout2d &size) const;
};