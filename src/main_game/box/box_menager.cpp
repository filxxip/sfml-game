#include "box_menager.h"
#include "box.h"

#include "../../../data/config_file.h"

BoxMenagerPart::BoxMenagerPart(std::pair<double, double> x_range_,
                               std::pair<double, double> y_range_)
    : x_range(x_range_), y_range(y_range_) {}

bool BoxMenagerPart::canBeInSpace(const CustomPicture::Ptr &picture) const {
  return canBeInSpace(picture->getPosition(), picture->getSize());
}

bool BoxMenagerPart::canBeInSpace(const tgui::Layout2d &layout,
                                  const tgui::Layout2d &size) const {
  const auto x = layout.x.getValue();
  const auto y = layout.y.getValue();
  const auto x_max = layout.x.getValue() + size.x.getValue();
  const auto y_max = layout.y.getValue() + size.y.getValue();
  if (x > x_range.second || x_range.first > x_max) {
    return false;
  }
  if (y > y_range.second || y_range.first > y_max) {
    return false;
  }
  return true;
}

void BoxMenagerPart::addBox(Box::Ptr box) {
  box_vector.push_back(std::move(box));
}

bool BoxMenagerPart::isWidgetInsideAnyBox(const tgui::Layout2d &layout,
                                          const tgui::Layout2d &size) const {
  auto index = std::find_if(box_vector.begin(), box_vector.end(),
                            [&layout, &size](auto &box) {
                              return box->isWidgetInside(layout, size);
                            });
  return index != box_vector.end();
}

BoxMenager::BoxMenager(MainGameComponents &components_)
    : box_size(BoxData::SIZE), components(components_) {
  createBoxesData();
}

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

void BoxMenager::createBoxesData() {
  double max_x = components.window.getSize().x;
  double max_y =
      components.window.getSize().y - BoxData::DELTA_PANEL_Y_POSITION;
  auto elements_number_x = static_cast<int>(max_x / BoxData::SIZE);
  auto elements_number_y = static_cast<int>(max_y / BoxData::SIZE);
  max_indexes = {elements_number_x - 1, elements_number_y - 1};
  double break_space_x = elements_number_x > 1
                             ? (max_x - elements_number_x * BoxData::SIZE) /
                                   static_cast<double>(elements_number_x - 1)
                             : break_space_x = 0;
  double break_space_y = elements_number_y > 1
                             ? (max_y - elements_number_y * BoxData::SIZE) /
                                   static_cast<double>(elements_number_y - 1)
                             : break_space_y = 0;

  box_element_size = {break_space_x + box_size,
                      break_space_y + box_size}; // gdzies to trzeba przezucic
}

void BoxMenager::addBox(double position_x, double position_y) {
  tgui::Layout2d lay(position_x, position_y);
  auto box = BoxFactory::create(components, BoxFactory::Types::STONE);
  for (auto &menager_box : menager_vector) {
    if (menager_box.canBeInSpace(lay, box->getPicture()->getSize())) {
      menager_box.addBox(box);
    }
  }

  box->put(position_x, position_y);
}

void BoxMenager::addBox(std::pair<int, int> indexes) {
  addBox(indexes.first * box_element_size.first,
         indexes.second * box_element_size.second);
}

void BoxMenager::createEdges() {

  addBox(200, 200);
  addBox({5, 2});
  addBox({5, 1});
  addBox({5, 3});
  addBox({5, 4});
  addBox({5, 5});
  addBox({5, 6});
  addBox({5, 7});

  addBox({2, 8});
  for (int i = 0; i <= max_indexes.first; i++) {
    addBox({i, 0});
    addBox({i, max_indexes.second});
  }
  for (int i = 1; i <= max_indexes.second - 1; i++) {
    addBox({0, i});
    addBox({max_indexes.first, i});
  }
}

void BoxMenager::initialize() {
  inittializeBoxes(15);
  createEdges();
}

bool BoxMenager::isPositionFree(const tgui::Layout2d &layout,
                                const tgui::Layout2d &size) const {
  for (auto &menager_box : menager_vector) {
    if (menager_box.canBeInSpace(layout, size)) {
      if (menager_box.isWidgetInsideAnyBox(layout, size)) {
        return false;
      }
    }
  }
  return true;
}
