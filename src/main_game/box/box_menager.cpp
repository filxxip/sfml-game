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

bool BoxMenagerPart::canBeInSpace(const CustomPicture::Ptr &picture) const {
  return canBeInSpace(picture->getPosition(), picture->getSize());
}

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
  std::cout << maximum_elements_x.toString() << "xxxx    "
            << maximum_elements_y.toString() << std::endl;
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
      // std::cout << init_width << " " << init_height << " " << end_width << "
      // "
      //           << end_height << "tututu" << std::endl;
      init_width += width;
      end_width += width;
    }
    std::cout << std::endl;
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

void BoxMenager::addBox(tgui::Layout2d &&positions, BoxFactory::Types type) {
  auto box = BoxFactory::create(components, type);
  box->put(positions.x.getValue(), positions.y.getValue());
  for (auto &menager_box : menager_vector) {
    if (menager_box.canBeInSpace(positions, box->getPicture()->getSize())) {
      menager_box.addBox(box);
    }
  }

  // box->put(positions.x.getValue(), positions.y.getValue());
}

void BoxMenager::addStone(tgui::Layout2d &&indexes) {
  addBox({indexes.x.getValue() * box_element_size.first,
          indexes.y.getValue() * box_element_size.second},
         BoxFactory::Types::STONE);
}

void BoxMenager::addBox(tgui::Layout2d &&indexes) {
  addBox({indexes.x.getValue() * box_element_size.first,
          indexes.y.getValue() * box_element_size.second},
         BoxFactory::Types::BOX);
}

void BoxMenager::createEdges() {

  addBox({5, 2});
  addBox({5, 1});
  addBox({5, 3});
  addBox({5, 4});
  addBox({5, 5});
  addBox({5, 6});
  addBox({5, 7});

  addBox({2, 8});
  for (int i = 0; i <= max_indexes.first; i++) {
    addStone({i, 0});
    addStone({i, max_indexes.second});
  }
  for (int i = 1; i <= max_indexes.second - 1; i++) {
    addStone({0, i});
    addStone({max_indexes.first, i});
  }
}

void BoxMenager::initialize() {
  inittializeBoxes(15);
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
