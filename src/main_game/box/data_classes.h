#pragma once

#include "../../../data/config_file.h"
#include "TGUI/Widget.hpp"
#include "string"

class Range {
private:
  double max;
  double min;

public:
  Range(double min_, double max_);
  double getMax() const;
  void setMax(double new_max);
  double getMin() const;
  void setMin(double new_min);
  std::string toString();
};

class Index {
private:
  int x;
  int y;

public:
  Index(int x_, int y_);
  tgui::Layout2d convertToPosition() const;
  tgui::Layout2d convertToPosition(double element_size) const;
  tgui::Layout2d convertToPosition(double element_size_x,
                                   double element_size_y) const;
  bool isValid() const;

  int getX() const;
  int getY() const;
};