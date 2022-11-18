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

  //   return ((x_range.first <= x && x_range.second > x) ||
  //           (x_range.first <= x_max && x_range.second > x_max)) &&
  //          ((y_range.first <= y && y_range.second > y) ||
  //           (y_range.first <= y_max && y_range.second > y_max));
}

void BoxMenagerPart::addBox(Box &&box) { box_vector.push_back(std::move(box)); }

bool BoxMenagerPart::isWidgetInsideAnyBox(const tgui::Layout2d &layout,
                                          const tgui::Layout2d &size) const {
  auto index = std::find_if(
      box_vector.begin(), box_vector.end(),
      [&layout, &size](auto &box) { return box.isWidgetInside(layout, size); });
  return index != box_vector.end();
}

BoxMenager::BoxMenager(MainGameComponents &components_)
    : components(components_) {}

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

void BoxMenager::addBox(double position_x, double position_y) {
  tgui::Layout2d lay(position_x, position_y);
  auto box = Box(components);
  //   auto index = std::find_if(
  //       menager_vector.begin(), menager_vector.end(),
  //       [&lay, size = box.getPicture()->getSize()](auto &menager_box) {
  //         return menager_box.canBeInSpace(lay, size);
  //       });

  for (auto &menager_box : menager_vector) {
    if (menager_box.canBeInSpace(lay, box.getPicture()->getSize())) {
      menager_box.addBox(std::move(
          box)); // problem z przechodzeniem miedyz boxami niektore boxy
                 // zaczynaja sie w innym niz mozna w nie wejsc, dobrym pomyslem
                 // jest shared pointer zamast oryginalnego obiektu w vectorze w
                 // kazdym boxie wtedy gdy nawet maly punkt danej instanci box
                 // znajdzie sie w jakims wiekszym boxie zostanie zarty w
                 // docelowym wiekszym boxie
    }
  }

  //   if (index != menager_vector.end()) {
  box.put(position_x, position_y);
  //     index->addBox(std::move(box));
  //   }
}

void BoxMenager::createEdges() {
  double max_x = components.window.getSize().x;
  double max_y =
      components.window.getSize().y - BoxData::DELTA_PANEL_Y_POSITION;
  auto elements_number_x = static_cast<int>(max_x / BoxData::SIZE);
  auto elements_number_y = static_cast<int>(max_y / BoxData::SIZE);

  double break_space_x = elements_number_x > 1
                             ? (max_x - elements_number_x * BoxData::SIZE) /
                                   static_cast<double>(elements_number_x - 1)
                             : break_space_x = 0;
  double break_space_y = elements_number_y > 1
                             ? (max_y - elements_number_y * BoxData::SIZE) /
                                   static_cast<double>(elements_number_y - 1)
                             : break_space_y = 0;

  for (int i = 0; i < elements_number_x; i++) {
    addBox(i * break_space_x + i * BoxData::SIZE, 0);
    addBox(i * break_space_x + i * BoxData::SIZE, max_y - BoxData::SIZE);
  }
  for (int i = 1; i < elements_number_y - 1; i++) {
    addBox(0, i * break_space_y + i * BoxData::SIZE);
    addBox(max_x - BoxData::SIZE, i * break_space_y + i * BoxData::SIZE);
  }
}

void BoxMenager::initialize() {
  inittializeBoxes(BoxData::DEFAULT_BOX_SPACES);
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

  //   auto index = std::find_if(menager_vector.begin(), menager_vector.end(),
  //                             [&layout](auto &menager_box) {
  //                               return menager_box.canBeInSpace(layout);
  //                             });
  //   return !index->isWidgetInsideAnyBox(layout, size);
}
