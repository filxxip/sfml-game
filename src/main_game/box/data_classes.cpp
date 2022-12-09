#include "data_classes.h"

Range::Range(double min_, double max_) : max(max_), min(min_) {}

double Range::getMax() const { return max; }

void Range::setMax(double new_max) { max = new_max; }

double Range::getMin() const { return min; }

void Range::setMin(double new_min) { min = new_min; }

std::string Range::toString() const {
  return "range: (" + std::to_string(min) + " , " + std::to_string(max) + ")";
}

Index::Index(int x_, int y_) : x(x_), y(y_) {}

tgui::Layout2d Index::convertToPosition() const {
  return convertToPosition(BoxData::ScaleMenager::getBoxSize(),
                           BoxData::ScaleMenager::getBoxSize());
}

tgui::Layout2d Index::convertToPosition(double element_size) const {
  return convertToPosition(element_size, element_size);
}

tgui::Layout2d Index::convertToPosition(double element_size_x,
                                        double element_size_y) const {

  return tgui::Layout2d(
      x * BoxData::ScaleMenager::getIndexBoxWidth() +
          0.5 * (BoxData::ScaleMenager::getIndexBoxWidth() - element_size_x),
      y * BoxData::ScaleMenager::getIndexBoxHeight() +
          0.5 * (BoxData::ScaleMenager::getIndexBoxHeight() - element_size_y));
}

tgui::Layout2d Index::convertToInitPosition() const {

  return tgui::Layout2d(x * BoxData::ScaleMenager::getIndexBoxWidth(),
                        y * BoxData::ScaleMenager::getIndexBoxHeight());
}

// bool Index::isValid() const {
//   if (x > 0 && x < BoxData::ScaleMenager::getMaxXIndex()) {
//     if (y > 0 && y < BoxData::ScaleMenager::getMaxYIndex()) {
//       return true;
//     }
//   }
//   return false;
// }

int Index::getX() const { return x; }
int Index::getY() const { return y; }

Index Index::getIndexFromPosition(CustomPicture::Ptr picture) {
  return getIndexFromPosition(picture->getSize(), picture->getPosition());
}

Index Index::getIndexFromPosition(tgui::Layout2d &&size,
                                  tgui::Layout2d &&position) {
  auto x =
      (position.x + 0.5 * size.x) / BoxData::ScaleMenager::getIndexBoxWidth();
  auto y =
      (position.y + 0.5 * size.y) / BoxData::ScaleMenager::getIndexBoxHeight();
  return Index(x.getValue(), y.getValue());
}
Index Index::operator+(const Index &other_index) {
  auto new_x = x + other_index.getX();
  auto new_y = y + other_index.getY();
  return Index(new_x, new_y);
}

bool Index::operator==(const Index &other_index) {
  return other_index.getX() == x && other_index.getY() == y;
}

std::string Index::toString() const {
  return "index: (" + std::to_string(x) + " , " + std::to_string(y) + ")";
}