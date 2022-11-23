#include "box_menager.h"
#include "box.h"

#include "../../../data/config_file.h"

BoxMenagerPart::BoxMenagerPart(Range &&x_range_, Range &&y_range_)
    : x_range(x_range_), y_range(y_range_),
      maximum_elements_x(
          {x_range.getMin() + (x_range.getMax() - x_range.getMin()) / 2,
           x_range.getMin() + (x_range.getMax() - x_range.getMin()) / 2}),
      maximum_elements_y(
          {y_range.getMin() + (y_range.getMax() - y_range.getMin()) / 2,
           y_range.getMin() + (y_range.getMax() - y_range.getMin()) / 2}) {}

// bool BoxMenagerPart::canBeInSpace(const CustomPicture::Ptr &picture) const {
//   return canBeInSpace(picture->getPosition(), picture->getSize());
// }

bool BoxMenagerPart::canBeInSpace(const tgui::Layout2d &layout,
                                  const tgui::Layout2d &size) const {
  const auto x = layout.x.getValue();
  const auto y = layout.y.getValue();
  const auto x_max = layout.x.getValue() + size.x.getValue();
  const auto y_max = layout.y.getValue() + size.y.getValue();
  // std::cout << "ilosc" << box_vector.size() << "----" << layout.toString()
  //           << "----" << size.toString() << std::endl;
  if (x > x_range.getMax() || x_range.getMin() > x_max) {
    return false;
  }
  if (y > y_range.getMax() || y_range.getMin() > y_max) {
    return false;
  }
  return true;
}

bool BoxMenagerPart::canBeInsideAnyBox(const tgui::Layout2d &layout,
                                       const tgui::Layout2d &size) const {
  const auto x = layout.x.getValue();
  const auto y = layout.y.getValue();
  const auto x_max = layout.x.getValue() + size.x.getValue();
  const auto y_max = layout.y.getValue() + size.y.getValue();
  if (x > maximum_elements_x.getMax() || maximum_elements_x.getMin() > x_max) {
    return false;
  }
  if (y > maximum_elements_y.getMax() || maximum_elements_y.getMin() > y_max) {
    return false;
  }
  return true;
}

void BoxMenagerPart::addBox(Box::Ptr box) {
  auto position = box->getPicture()->getPosition();
  auto size = box->getPicture()->getSize();
  auto maximum_x = position.x + size.x;
  auto maximum_y = position.y + size.y;
  if (maximum_elements_x.getMin() > position.x) {
    maximum_elements_x.setMin(position.x);
  }
  if (maximum_elements_y.getMin() > position.y) {
    maximum_elements_y.setMin(position.y);
  }
  if (maximum_elements_x.getMax() < maximum_x) {
    maximum_elements_x.setMax(maximum_x);
  }
  if (maximum_elements_y.getMax() < maximum_y) {
    maximum_elements_y.setMax(maximum_y);
  }
  box_vector.push_back(box);
}

bool BoxMenagerPart::isWidgetInsideAnyBox(const tgui::Layout2d &layout,
                                          const tgui::Layout2d &size) const {
  auto index = std::find_if(box_vector.begin(), box_vector.end(),
                            [&layout, &size](auto &box) {
                              return box->isWidgetInside(layout, size);
                            });
  return index != box_vector.end();
}

BoxMenager::BoxMenager(MainGameComponents &components_, const Player &player_)
    : components(components_), player(player_) {}

void BoxMenager::inittializeBoxes(int count) {
  double width = components.window.getSize().x;
  double height =
      components.window.getSize().y - PanelData::DELTA_PANEL_Y_POSITION;
  width = width / count;
  height = height / count;
  double init_height = 0;
  double end_height = height;
  for (int i = 0; i < count; i++) {
    double init_width = 0;
    double end_width = width;
    for (int j = 0; j < count; j++) {
      menager_vector.push_back(
          BoxMenagerPart({init_width, end_width}, {init_height, end_height}));
      init_width += width;
      end_width += width;
    }
    init_height += height;
    end_height += height;
  }
}

// std::pair<int, int> BoxMenager::getMaxXIndexes() const {
//   auto x_min = 1;
//   auto x_max = max_indexes.first - 1;
//   return std::pair<int, int>(x_min, x_max);
// };

// std::pair<int, int> BoxMenager::getMaxYIndexes() const {
//   auto y_min = 1;
//   auto y_max = max_indexes.second - 1;
//   return std::pair<int, int>(y_min, y_max);
// };

void BoxMenager::createBoard() {
  srand((unsigned)time(NULL));
  for (int i = 0; i < 140; i++) {
    while (true) {
      auto max_x = BoxData::ELEMENTS_X - 1;
      auto min_x = 1;
      int randomx = rand() % (max_x - min_x + 1) + min_x;
      auto max_y = BoxData::ELEMENTS_Y - 1;
      auto min_y = 1;
      int randomy = rand() % (max_y - min_y + 1) + min_y;
      if (areIndexesFree({randomx, randomy})) {
        addBox({randomx, randomy});
        break;
      }
    }
  }
}

// void BoxMenager::createBoxesData() {
//   double max_x = components.window.getSize().x;
//   double max_y =
//       components.window.getSize().y - BoxData::DELTA_PANEL_Y_POSITION;
//   auto elements_number_x = static_cast<int>(max_x / BoxData::SIZE);
//   auto elements_number_y = static_cast<int>(max_y / BoxData::SIZE);

//   // max_indexes = {elements_number_x - 1, elements_number_y - 1};
//   double break_space_x = elements_number_x > 1
//                              ? (max_x - elements_number_x * BoxData::SIZE) /
//                                    static_cast<double>(elements_number_x - 1)
//                              : break_space_x = 0;
//   double break_space_y = elements_number_y > 1
//                              ? (max_y - elements_number_y * BoxData::SIZE) /
//                                    static_cast<double>(elements_number_y - 1)
//                              : break_space_y = 0;

//   // box_element_size = {break_space_x + box_size,
//   //                     break_space_y + box_size}; // gdzies to trzeba
//   //                     przezucic
//   // Index::initialize({break_space_x + box_size, break_space_y + box_size},
//   //                   {elements_number_x - 1, elements_number_y - 1});
// }

void BoxMenager::addBox(Index &&index, BoxFactory::Types type) {
  auto pos = index.convertToPosition();
  if (isPositionFree(pos)) {
    auto box = BoxFactory::create(components, type);
    box->put(pos.x.getValue(), pos.y.getValue());
    for (auto &menager_box : menager_vector) {
      if (menager_box.canBeInSpace(pos, box->getPicture()->getSize())) {
        menager_box.addBox(box);
      }
    }
  }

  // box->put(positions.x.getValue(), positions.y.getValue());
}

void BoxMenager::addStone(Index &&indexes) {
  addBox(std::move(indexes), BoxFactory::Types::STONE);
}

void BoxMenager::addBox(Index &&indexes) {
  addBox(std::move(indexes), BoxFactory::Types::BOX);
}

void BoxMenager::createEdges() {
  for (int i = 0; i <= BoxData::ELEMENTS_X - 1; i++) {
    addStone({i, 0});
    addStone({i, BoxData::ELEMENTS_Y - 1});
  }
  for (int i = 1; i <= BoxData::ELEMENTS_Y - 1 - 1; i++) {
    addStone({0, i});
    addStone({BoxData::ELEMENTS_X - 1, i});
  }
}

// bool BoxMenager::areIndexesValid(std::pair<int, int> indexes) const {
//   return indexes.first >= getMaxXIndexes().first &&
//          indexes.first <= getMaxXIndexes().second &&
//          indexes.second >= getMaxYIndexes().first &&
//          indexes.second <= getMaxYIndexes().second;
// }

void BoxMenager::initialize() {
  inittializeBoxes(15);
  createBoard();
  createEdges();
}

bool BoxMenager::isPositionFree(const tgui::Layout2d &layout,
                                const tgui::Layout2d &size) const {
  for (auto &menager_box : menager_vector) {
    if (menager_box.canBeInsideAnyBox(layout, size)) {
      if (menager_box.isWidgetInsideAnyBox(layout, size)) {
        return false;
      }
    }
  }
  return true;
}
bool BoxMenager::isPositionFree(const tgui::Layout2d &layout) const {
  return isPositionFree(layout, {BoxData::SIZE, BoxData::SIZE});
}

bool BoxMenager::areIndexesFree(Index &&indexes) const {
  return indexes.isValid() && isPositionFree(indexes.convertToPosition());
}

// bool BoxMenager::areIndexesFree(Index &&indexes,
//                                 const tgui::Layout2d &size) const {
//   return areIndexesValid(indexes) &&
//          isPositionFree({indexes.first * box_element_size.first,
//                          indexes.second * box_element_size.second});
// }