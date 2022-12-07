#include "down_panel.h"
#include "../../../data/config_file.h"
#include "down_panel_elements.h"

template class ElementPanel<PanelElementsTypes::HeartType>;
template class ElementPanel<Bomb::BombType>;

template <typename T>
ElementPanel<T>::ElementPanel(MainGameComponents &components_)
    : components(components_),
      panel(CustomPicture::create(components.window, Paths::HEART_PANEL_PATH)),
      elements_number(5) {}

// template <typename t> class A;

template <typename T> decltype(auto) ElementPanel<T>::getFirstElementOn() {
  return std::find_if(elements.begin(), elements.end(),
                      [](auto &element) { return element->isOn(); });
}
template <typename T>
decltype(auto) ElementPanel<T>::getFirstElementOn() const {
  return std::find_if(elements.cbegin(), elements.cend(),
                      [](auto &element) { return element->isOn(); });
}

template <typename T> int ElementPanel<T>::getActiveElementNumber() const {
  auto distance = std::distance(elements.begin(), getFirstElementOn());
  return elements_number - std::distance(elements.begin(), getFirstElementOn());
}

template <typename T> void ElementPanel<T>::removeElement() {
  components.gui.remove(elements.at(elements.size() - 1));
  elements.erase(
      elements.end() -
      1); // pewnie cos trzeba z setsize i setposition ale mi sie nie chce
}
template <typename T>
void ElementPanel<T>::addNewElement(const std::string &path) {
  elements.push_back(createElement(path));
}

template <typename T> void ElementPanel<T>::switchOnNextElement() {
  auto first = getFirstElementOn();
  // (*elements.end())->get()->setOff();
  if (first != elements.end()) {
    first->get()->setOff();
  }
}

template <typename T> void ElementPanel<T>::switchOnPreviousElement() {
  auto element = getFirstElementOn();
  if (element != elements.begin()) {
    std::prev(element)->get()->setOn();
  }
}

template <typename T> T ElementPanel<T>::getCurrentType() const {
  return getFirstElementOn()->get()->getType();
}

template <typename T> void ElementPanel<T>::changeCurrentElement() {
  getFirstElementOn()->get()->changeType();
}

template <typename T> void ElementPanel<T>::setSize() {
  panel->setSize(
      elements.size() *
              Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE) +
          2 * Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_MARGIN) +
          (elements.size() - 1) *
              Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SPACING),
      Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE) +
          2 * Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_MARGIN));
}
template <typename T> void ElementPanel<T>::setPosition(int y, int x) {
  panel->setPosition(x, y);
  int first_pos =
      x + Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_MARGIN);
  for (auto &element : elements) {
    element->setPosition(
        first_pos,
        y + Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_MARGIN));
    first_pos +=
        Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SPACING) +
        Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE);
  }
} // dokonczyc refaktoryzacje

template <typename T> void ElementPanel<T>::initialize(int x_position) {
  components.gui.add(panel);
  createElements();
  setPosition(components.window.getSize().y -
                  Scaler::getPanelElementSize(
                      Scaler::PanelElement::DELTA_PANEL_Y_POSITION_HEIGHT),
              x_position);
  setSize();
  for (auto &element : elements) {
    components.gui.add(element);
  }
}

template <typename T>
typename PanelElement<T>::Ptr
ElementPanel<T>::initializeElement(const std::string &path) {
  auto element = createElement(path);
  element->setSize(
      Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE),
      Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE));
  elements.push_back(element);
  return element;
}

template <typename T> void ElementPanel<T>::remove() {
  components.gui.remove(panel);
  for (auto &element : elements) {
    components.gui.remove(element);
  }
  elements.clear();
}

BombPanel::BombPanel(MainGameComponents &components_)
    : ElementPanel<Bomb::BombType>(components_) {
  elements_number = 3;
}
void BombPanel::createElements() {
  for (int i = 0; i < elements_number; i++) {
    initializeElement(Paths::BOMB_PATH);
  }
}

PanelElement<Bomb::BombType>::Ptr
BombPanel::createElement(const std::string &path) {
  return BombElement::create(components.window, path);
}

void BombPanel::initialize() { ElementPanel<Bomb::BombType>::initialize(600); }

HeartPanel::HeartPanel(MainGameComponents &components_)
    : ElementPanel<PanelElementsTypes::HeartType>(components_) {}

void HeartPanel::createElements() {
  for (int i = 0; i < elements_number; i++) {
    initializeElement(Paths::RED_HEART_PATH);
  }
}

PanelElement<PanelElementsTypes::HeartType>::Ptr
HeartPanel::createElement(const std::string &path) {
  return HeartElement::create(components.window, path);
}

void HeartPanel::initialize() {
  ElementPanel<PanelElementsTypes::HeartType>::initialize(200);
}

void HeartPanel::addHeart() {
  auto heart = HeartElement::create(components.window, Paths::RED_HEART_PATH);
  heart->setSize(
      Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE),
      Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE));
  elements.push_back(heart);
  components.gui.add(heart);
  setSize();
  setPosition(components.window.getSize().y -
                  Scaler::getPanelElementSize(
                      Scaler::PanelElement::DELTA_PANEL_Y_POSITION_HEIGHT),
              200);
  elements_number++;
}
// decltype(auto) HeartElement::getFirstOnElement() {
//   return std::find_if(index_map.begin(), index_map.end(),
//                       [index](auto &pair) { return index == pair.second;
//                       })
// }

// std::unordered_map<HeartElement::Type, int> HeartElement::index_map{
//     {Type::GREY, 0}, {Type::RED, 1}};
// <
// DownPanel::DownPanel(MainGameComponents &components_)
//     : components(components_),
//       hearts_panel(
//           CustomPicture::create(components.window,
//           Paths::HEART_PANEL_PATH))
//           {
//   current_bomb = CustomPicture::create(components.window,
//   Paths::BOMB_PATH);
// }

// void DownPanel::removeHeart() {
//   if (active_hearts != 0) {
//     hearts.at(active_hearts - 1)->changeType();
//     active_hearts--;
//   }
// }

// void DownPanel::addHeart() {
//   if (active_hearts == hearts.size()) {
//     if (isHeartNumberValid(hearts.size() + 1)) {
//       auto heart = createHeart();
//       components.gui.add(heart);
//       setSize();
//       setPosition(components.window.getSize().y -
//                   Scaler::getPanelElementSize(
//                       Scaler::PanelElement::DELTA_PANEL_Y_POSITION_HEIGHT));
//       active_hearts++;
//     }
//   } else {
//     hearts.at(active_hearts)->changeType();
//     active_hearts++;
//   }
// }

// void DownPanel::changeHeartStatus(int index) {
// hearts.at(index)->changeType(); }

// void DownPanel::setPosition(int y) {
//   setHeartsPosition(
//       Scaler::getPanelElementSize(Scaler::PanelElement::HEART_X_POSITION),
//       y);
//   current_bomb->setPosition(
//       components.window.getSize().x -
//           Scaler::getPanelElementSize(Scaler::PanelElement::BOMB_SUP_POS),
//       y);
// }

// void DownPanel::setSize() {
//   hearts_panel->setSize(
//       hearts.size() *
//               Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE)
//               +
//           2 *
//           Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_MARGIN)
//           + (hearts.size() - 1) *
//               Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SPACING),
//       Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE) +
//           2 *
//           Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_MARGIN));
//   current_bomb->setSize(
//       Scaler::getPanelElementSize(Scaler::PanelElement::BOMB_SIZE),
//       Scaler::getPanelElementSize(Scaler::PanelElement::BOMB_SIZE));
// }

// void DownPanel::setHeartsPosition(int x, int y) {
//   hearts_panel->setPosition(x, y);
//   int first_pos =
//       x +
//       Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_MARGIN);
//   for (auto &heart : hearts) {
//     heart->setPosition(first_pos, y + Scaler::getPanelElementSize(
//                                           Scaler::PanelElement::HEARTS_MARGIN));
//     first_pos +=
//         Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SPACING)
//         + Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE);
//   }
// }
// Heart::Ptr DownPanel::createHeart() {
//   auto heart = Heart::create(components.window, Paths::RED_HEART_PATH);
//   heart->setSize(
//       Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE),
//       Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE));
//   hearts.push_back(heart);
//   return heart;
// }

// bool DownPanel::isHeartNumberValid(int number) {
//   return number <= 10 && number > 0;
// }

// void DownPanel::createHearts(int hearts_number) {
//   if (!isHeartNumberValid(hearts_number)) {
//     hearts_number = PanelData::DEFAULT_HEART_NUMBER;
//   }
//   for (int i = 0; i < hearts_number; i++) {
//     createHeart();
//   }
// }

// void DownPanel::initialize() {
//   components.gui.add(current_bomb);
//   components.gui.add(hearts_panel);
//   active_hearts = PanelData::DEFAULT_HEART_NUMBER;
//   createHearts(active_hearts);
//   setPosition(components.window.getSize().y -
//               Scaler::getPanelElementSize(
//                   Scaler::PanelElement::DELTA_PANEL_Y_POSITION_HEIGHT));
//   setSize();
//   for (auto &heart : hearts) {
//     components.gui.add(heart);
//   }
// }

// void DownPanel::remove() {
//   components.gui.remove(current_bomb);
//   components.gui.remove(hearts_panel);
//   for (auto &heart : hearts) {
//     components.gui.remove(heart);
//   }
//   hearts.clear();
// }

// void DownPanel::setBomb(Bomb::BombType bomb_type) {
//   current_bomb->setPicture(Bomb::bomb_names.at(bomb_type));
// }

// const int DownPanel::getHeartNumber() const { return active_hearts; }>