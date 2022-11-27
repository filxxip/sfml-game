#include "box_menager.h"
#include "box.h"

#include "../../../data/config_file.h"

PartMenager::PartMenager(MainGameComponents &components_, Range &&x_range_,
                         Range &&y_range_)
    : x_range(x_range_), y_range(y_range_), components(components_),
      maximum_elements_x(
          {x_range.getMin() + (x_range.getMax() - x_range.getMin()) / 2,
           x_range.getMin() + (x_range.getMax() - x_range.getMin()) / 2}),
      maximum_elements_y(
          {y_range.getMin() + (y_range.getMax() - y_range.getMin()) / 2,
           y_range.getMin() + (y_range.getMax() - y_range.getMin()) / 2}) {}

PartMenager::PartMenager(MainGameComponents &components_)
    : PartMenager(components_, Range(0, components_.window.getSize().x),
                  Range(0, components_.window.getSize().y)) {}

bool PartMenager::canBeInSpace(const tgui::Layout2d &layout,
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

bool PartMenager::canBeInsideAnyItem(const tgui::Layout2d &layout,
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

void PartMenager::addItem(GamePicture::Ptr item) {
  auto position = item->getPosition();
  auto size = item->getSize();
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
  box_vector.push_back(item);
}

bool PartMenager::isWidgetInsideAnyItem(const tgui::Layout2d &layout,
                                        const tgui::Layout2d &size) const {
  auto index = std::find_if(box_vector.begin(), box_vector.end(),
                            [&layout, &size](auto &box) {
                              return box->isWidgetInside(layout, size);
                            });
  return index != box_vector.end();
}

void PartMenager::destroy() {

  for (auto &item : box_vector) {
    components.gui.remove(item);
  }
  box_vector.clear();
}

void PartMenager::removeEveryExpiredItem(bool game_is_running) {
  auto index = std::remove_if(box_vector.begin(), box_vector.end(),
                              [game_is_running](auto &fire) {
                                return fire->isExpired(game_is_running);
                              });
  box_vector.erase(index, box_vector.end());
}

void PartMenager::checkExpired(bool game_is_running) {
  for (auto &fire : box_vector) {
    // fire->measure(game_is_running);
    if (fire->isExpired(game_is_running)) {
      components.gui.remove(fire); // to remoeve
    }
  }

  auto new_end = std::remove_if(box_vector.begin(), box_vector.end(),
                                [game_is_running](auto &fire) {
                                  return fire->isExpired(game_is_running);
                                });
  box_vector.erase(
      new_end,
      box_vector.end()); // wywalic sprawdzenie indeksow i tak bez sensu
}

bool PartMenager::isPositionFree(const tgui::Layout2d &layout,
                                 const tgui::Layout2d &size) const {
  return !(canBeInsideAnyItem(layout, size) &&
           isWidgetInsideAnyItem(layout, size));
}

BoxMenager::BoxMenager(MainGameComponents &components_, const Player &player_)
    : components(components_), player(player_), fire_menager(components_) {}

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
      menager_vector.push_back(PartMenager(components, {init_width, end_width},
                                           {init_height, end_height}));
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
    box.destroy();
  }
  fire_menager.destroy();
  menager_vector.clear();
}
void BoxMenager::addItem(Index &&index, GamePicture::Ptr &&item) {
  auto pos = index.convertToPosition();
  if (isPositionFree(pos)) {
    item->setIndexPosition(std::move(index));
    components.gui.add(item);
    for (auto &menager_box : menager_vector) {
      if (menager_box.canBeInSpace(pos, item->getSize())) {
        std::cout << "hello" << std::endl;
        menager_box.addItem(item);
      }
    }
  }
}
void BoxMenager::addStone(Index &&indexes) {
  addItem(std::move(indexes), Stone::create(components));
}
void BoxMenager::addBox(Index &&indexes) {
  addItem(std::move(indexes), Box::create(components));
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
    if (!menager_box.isPositionFree(layout, size)) {
      return false;
    }
  }
  return true;
}
bool BoxMenager::isPositionFree(const tgui::Layout2d &layout) const {
  return isPositionFree(layout, {BoxData::ScaleMenager::getBoxSize(),
                                 BoxData::ScaleMenager::getBoxSize()});
}

bool BoxMenager::isFromFirePositionFree(const tgui::Layout2d &layout,
                                        const tgui::Layout2d &size) const {
  return fire_menager.isPositionFree(layout, size);
}
bool BoxMenager::isEntirePositionFree(const tgui::Layout2d &layout,
                                      const tgui::Layout2d &size) const {
  return isPositionFree(layout, size) && isFromFirePositionFree(layout, size);
}

bool BoxMenager::areIndexesFree(const Index &indexes) const {
  return isPositionFree(indexes.convertToPosition());
}

void BoxMenager::backendFireCreator(Index &&init_index, bool &condition) {
  if (condition) {
    if (areIndexesFree(init_index)) {
      addFire(std::move(init_index));
    } else {
      condition = false;
    }
  }
}

void BoxMenager::createWholeFire(Index &&init_index, int bomb_power) {
  bool is_right_path_free = true;
  bool is_left_path_free = true;
  bool is_up_path_free = true;
  bool is_down_path_free = true;
  backendFireCreator(init_index + Index(0, 0), is_down_path_free);
  // std::cout << bomb_power << std::endl;
  for (int i = 1; i < bomb_power; i++) {
    backendFireCreator(init_index + Index(0, i), is_down_path_free);
    backendFireCreator(init_index + Index(i, 0), is_right_path_free);
    backendFireCreator(init_index + Index(-i, 0), is_left_path_free);
    backendFireCreator(init_index + Index(0, -i), is_up_path_free);
  }
}

void BoxMenager::addFire(Index &&index) {
  // std::cout << "tworze" << std::endl;
  auto fire = Fire::create(components);
  fire->setIndexPosition(std::move(index));
  components.gui.add(fire);
  fire_menager.addItem(std::move(fire));
  // fire_menager.push_back(std::move(fire));
}

// void FireMenager::removeEveryExpiredFire() {
//   auto index = std::remove_if(box_vector.begin(), box_vector.end(),
//                               [](auto &fire) { return fire->isExpired(); });
//   box_vector.erase(index, box_vector.end());
// }

void BoxMenager::checkFiresExpired(bool game_is_running) {
  fire_menager.checkExpired(game_is_running);
  // auto new_end = std::remove_if(
  //     box_vector.begin(), box_vector.end(),
  //     [game_is_running](auto &fire) { return fire->isExpired(); });
  // box_vector.erase(new_end, fire_vector.end());
}