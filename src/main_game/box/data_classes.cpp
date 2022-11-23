#include "data_classes.h"

Range::Range(double min_, double max_) : max(max_), min(min_) {}

double Range::getMax() const { return max; }

void Range::setMax(double new_max) { max = new_max; }

double Range::getMin() const { return min; }

void Range::setMin(double new_min) { min = new_min; }

std::string Range::toString() {
  return "range: (" + std::to_string(min) + " , " + std::to_string(max) + ")";
}

Index::Index(int x_, int y_) : x(x_), y(y_) {}

tgui::Layout2d Index::convertToPosition() const {
  return convertToPosition(BoxData::SIZE, BoxData::SIZE);
}

tgui::Layout2d Index::convertToPosition(double element_size) const {
  return convertToPosition(element_size, element_size);
}

tgui::Layout2d Index::convertToPosition(double element_size_x,
                                        double element_size_y) const {
  return tgui::Layout2d(x * BoxData::INDEX_BOX_WIDTH +
                            0.5 * (BoxData::INDEX_BOX_WIDTH - element_size_x),
                        y * BoxData::INDEX_BOX_HEIGHT +
                            0.5 * (BoxData::INDEX_BOX_HEIGHT - element_size_y));
}

bool Index::isValid() const {
  if (x > 0 && x < BoxData::MAX_X_INDEX) {
    if (y > 0 && y < BoxData::MAX_Y_INDEX) {
      return true;
    }
  }
  return false;
}

int Index::getX() const { return x; }
int Index::getY() const { return y; }