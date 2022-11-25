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
           y_range.getMin() + (y_range.getMax() - y_range.getMin()) / 2}) {
  // std::cout
  //     <<
  //     BoxData::ScaleMenager<BoxData::SizeOptions::AVERAGE>::getBreakSpaceX()
  //     << "  " << BoxData::INDEX_BOX_WIDTH << " " << BoxData::ELEMENTS_X << "
  //     "
  //     << BoxData::BREAK_SPACE_Y << "  " << BoxData::INDEX_BOX_HEIGHT << " "
  //     << BoxData::ELEMENTS_Y << "   " << std::endl;
}

bool BoxMenagerPart::canBeInSpace(const tgui::Layout2d &layout,
                                  const tgui::Layout2d &size) const {
  const auto x = layout.x.getValue();
  const auto y = layout.y.getValue();
  const auto x_max = layout.x.getValue() + size.x.getValue();
  const auto y_max = layout.y.getValue() + size.y.getValue();
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

void BoxMenagerPart::destroy(MainGameComponents &components_) {

  for (auto &box : box_vector) {
    components_.gui.remove(box->getPicture());
  }
  box_vector.clear();
}

BoxMenager::BoxMenager(MainGameComponents &components_, const Player &player_)
    : components(components_), player(player_) {}

void BoxMenager::inittializeBoxes(int count) {
  double width = components.window.getSize().x;
  double height = components.window.getSize().y -
                  BoxData::ScaleMenager::getPanelElementSize(
                      BoxData::ScaleMenager::PanelElement::
                          DEFAULT_DELTA_PANEL_Y_POSITION_HEIGHT);
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

void BoxMenager::createBoard() {
  std::vector<Index> possible_indexes;

  possible_indexes.reserve(BoxData::ScaleMenager::getMaxXIndex() *
                           BoxData::ScaleMenager::getMaxYIndex());

  for (int i = BoxData::ScaleMenager::getMinXIndex();
       i <= BoxData::ScaleMenager::getMaxXIndex(); i++) {
    for (int j = BoxData::ScaleMenager::getMinYIndex();
         j <= BoxData::ScaleMenager::getMaxYIndex(); j++) {
      if (!(i == 1 && j == 1) && !(i == 2 && j == 1) && !(i == 1 && j == 2)) {
        possible_indexes.emplace_back(i, j);
      }
    }
  }
  srand((unsigned)time(NULL));
  for (int i = 0; i < BoxData::ScaleMenager::getBoxesElementsNumber(); i++) {
    int randomx = rand() % possible_indexes.size();
    auto itr = possible_indexes.begin() + randomx;
    addBox(std::move(possible_indexes.at(randomx)));
    possible_indexes.erase(itr);
  }
  for (int i = 0; i < BoxData::ScaleMenager::getStonesElementsNumber(); i++) {
    int randomx = rand() % possible_indexes.size();
    auto itr = possible_indexes.begin() + randomx;
    addStone(std::move(possible_indexes.at(randomx)));
    possible_indexes.erase(itr);
  }
}

void BoxMenager::remove() {
  for (auto &box : menager_vector) {
    box.destroy(components);
  }
  menager_vector.clear();
}
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
}
void BoxMenager::addStone(Index &&indexes) {
  addBox(std::move(indexes), BoxFactory::Types::STONE);
}
void BoxMenager::addBox(Index &&indexes) {
  addBox(std::move(indexes), BoxFactory::Types::BOX);
}
void BoxMenager::createEdges() {
  for (int i = 0; i <= BoxData::ScaleMenager::getMaxXIndex() + 1; i++) {
    addStone({i, 0});
    addStone({i, BoxData::ScaleMenager::getElementsYNumber() - 1});
  }
  for (int i = 1; i <= BoxData::ScaleMenager::getMaxYIndex() + 1; i++) {
    addStone({0, i});
    addStone({BoxData::ScaleMenager::getElementsXNumber() - 1, i});
  }
}
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
  return isPositionFree(layout, {BoxData::ScaleMenager::getBoxSize(),
                                 BoxData::ScaleMenager::getBoxSize()});
}

bool BoxMenager::areIndexesFree(Index &&indexes) const {
  return indexes.isValid() && isPositionFree(indexes.convertToPosition());
}
