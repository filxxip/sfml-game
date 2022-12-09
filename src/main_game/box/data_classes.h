#pragma once

#include "../../../data/config_file.h"
#include "../../picture/picture.h"
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
  std::string toString() const;
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
  tgui::Layout2d convertToInitPosition() const;
  // bool isValid() const;

  int getX() const;
  int getY() const;

  Index operator+(const Index &other_index);
  bool operator==(const Index &other_index);

  double getIndexWidth() const {
    return BoxData::ScaleMenager::getIndexBoxWidth();
  }
  double getIndexHeight() const {
    return BoxData::ScaleMenager::getIndexBoxHeight();
  }

  tgui::Layout2d getIndexSize() const {
    return tgui::Layout2d(BoxData::ScaleMenager::getIndexBoxWidth(),
                          BoxData::ScaleMenager::getIndexBoxHeight());
  }

  static Index getIndexFromPosition(CustomPicture::Ptr picture);
  static Index getIndexFromPosition(tgui::Layout2d &&size,
                                    tgui::Layout2d &&position);
  std::string toString() const;
};

class EmptyIndex : public Index {
public:
  EmptyIndex() : Index(-1, -1) {}
};