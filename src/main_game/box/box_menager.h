#pragma once

#include "../../game/main_game_components/main_game_components.h"
#include "../../picture/picture.h"
#include "box.h"
#include <TGUI/Widget.hpp>
#include <utility>

class BoxMenagerPart {
private:
  std::pair<double, double> x_range;
  std::pair<double, double> y_range;

  std::vector<Box::Ptr> box_vector;

public:
  enum class Measure { X, Y };
  BoxMenagerPart(std::pair<double, double> x_range_,
                 std::pair<double, double> y_range_);
  bool canBeInSpace(const CustomPicture::Ptr &picture) const;
  bool canBeInSpace(const tgui::Layout2d &layout,
                    const tgui::Layout2d &size) const;
  bool isWidgetInsideAnyBox(const tgui::Layout2d &layout,
                            const tgui::Layout2d &size) const;
  void addBox(Box::Ptr box);
};

class BoxMenager {
private:
  std::vector<BoxMenagerPart> menager_vector;

  double box_size;
  std::pair<double, double> box_element_size;
  std::pair<int, int> max_indexes;

  void inittializeBoxes(int count);
  MainGameComponents &components;
  void createEdges();
  void createBoxesData();
  void addBox(double position_x, double position_y);
  // void addBoxItem(double position_x, double position_y);
  // void addStoneItem(double position_x, double position_y);

public:
  BoxMenager(MainGameComponents &components_);
  // void addBox(double position_x, double position_y);
  void addBox(std::pair<int, int> indexes);
  void initialize();
  bool isPositionFree(const tgui::Layout2d &layout,
                      const tgui::Layout2d &size) const;
};