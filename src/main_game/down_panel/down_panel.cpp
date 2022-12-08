#include "down_panel.h"
#include "../../../data/config_file.h"
#include "down_panel_elements.h"

template class ElementPanel<PanelElementsTypes::HeartType>;
template class ElementPanel<Bomb::BombType>;

template <typename T>
ElementPanel<T>::ElementPanel(MainGameComponents &components_)
    : components(components_),
      panel(CustomPicture::create(components.window, Paths::HEART_PANEL_PATH)),
      basic_elements_number(5) {}

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
  return getElementsSize() -
         std::distance(elements.begin(), getFirstElementOn());
}

template <typename T> void ElementPanel<T>::removeElement() {
  if (getElementsSize()>=0){
    components.gui.remove(elements.at(0));
  elements.erase(elements.begin());
  setSize();
  setPosition(createNewPositionAfterRemoving());
  }
}
template <typename T>
void ElementPanel<T>::addNewElement(const std::string &path) {
  if (getElementsSize()>=basic_elements_number && getActiveElementNumber()<getElementsSize()){
    switchOnPreviousElement();
    // setPosition()
  }else{
     initializeElement(path);
     setSize();
     setPosition(createNewPositionAfterAdding());
  }
  // setSize();
}

template <typename T> void ElementPanel<T>::switchOnNextElement() {
  auto first = getFirstElementOn();
  if (first != elements.end()) {
    first->get()->setOff();
  }
}

template <typename T> bool ElementPanel<T>::isAnyElementOn() const {
  return getFirstElementOn() != elements.end();
}

template <typename T> void ElementPanel<T>::switchOnPreviousElement() {
  auto element = getFirstElementOn();
  if (element != elements.begin()) {
    std::prev(element)->get()->setOn();
  }
  updateCurrentElement();
}

template <typename T> T ElementPanel<T>::getCurrentType() const {
  return getFirstElementOn()->get()->getType();
}

template <typename T> void ElementPanel<T>::changeCurrentElement() {
  getFirstElementOn()->get()->changeType();
}

template <typename T> void ElementPanel<T>::updateCurrentElement() {
  getFirstElementOn()->get()->changeStyle();
}

template <typename T> void ElementPanel<T>::changeEveryElement() {
  for (auto &element : elements) {
    element->changeType();
  }
}

template <typename T> void ElementPanel<T>::setSize() {
  if (getElementsSize()>=1){
    panel->setVisible(true);
    panel->setSize(
      elements.size() *
              Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE) +
          2 * Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_MARGIN) +
          (getElementsSize() - 1) *
              Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SPACING),
      Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE) +
          2 * Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_MARGIN));
  }else{
    panel->setVisible(false);
  }
}

template <typename T>
void ElementPanel<T>::setPosition(tgui::Layout2d &&layout) {
  panel->setPosition(layout);
  int first_pos =
      layout.getValue().x +
      Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_MARGIN);
  auto y_pos = layout.getValue().y +
               Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_MARGIN);
  auto my_function = [&first_pos, &y_pos](auto first_iter, auto second_iter) {
    std::for_each(first_iter, second_iter, [&first_pos, &y_pos](auto &element) {
      element->setPosition(first_pos, y_pos);
      first_pos +=
          Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SPACING) +
          Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE);
    });
  };
  switch (direction) {
  case Direction::RIGHT: {
    my_function(elements.begin(), elements.end());
    break;
  }
  case Direction::LEFT: {
    my_function(elements.rbegin(), elements.rend());
    break;
  }
  }
}

template <typename T> void ElementPanel<T>::initialize(int x_position) {
  components.gui.add(panel);
  createElements();
  setPosition(components.window.getSize().y -
                  Scaler::getPanelElementSize(
                      Scaler::PanelElement::DELTA_PANEL_Y_POSITION_HEIGHT),
              x_position);
  setSize();
  // for (auto &element : elements) {
  //   components.gui.add(element);
  // }
}

template <typename T>
typename PanelElement<T>::Ptr
ElementPanel<T>::initializeElement(const std::string &path) {
  auto element = createElement(path);
  element->setSize(
      Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE),
      Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE));
  elements.push_back(element);
  components.gui.add(element);
  return element;
}

template <typename T> void ElementPanel<T>::remove() {
  components.gui.remove(panel);
  for (auto &element : elements) {
    components.gui.remove(element);
  }
  elements.clear();
}

template <typename T>
tgui::Layout2d ElementPanel<T>::createNewPositionAfterAdding() {
  double new_x;
  switch (direction) {
  case Direction::RIGHT: {
    new_x = panel->getPosition().x;
    break;
  }
  case Direction::LEFT: {
    new_x = panel->getPosition().x -
            Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE) -
            Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SPACING);
    break;
  }
  }
  return tgui::Layout2d(new_x, panel->getPosition().y);
}

template <typename T>
tgui::Layout2d ElementPanel<T>::createNewPositionAfterRemoving() {
  double new_x;
  switch (direction) {
  case Direction::RIGHT: {
    new_x = panel->getPosition().x;
    break;
  }
  case Direction::LEFT: {
    new_x = panel->getPosition().x +
            Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE) +
            Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SPACING);
    break;
  }
  }
  return tgui::Layout2d(new_x, panel->getPosition().y);
}

BombPanel::BombPanel(MainGameComponents &components_)
    : ElementPanel<Bomb::BombType>(components_) {
  basic_elements_number = 3;
  direction = Direction::LEFT;
}
void BombPanel::createElements() {
  for (int i = 0; i < basic_elements_number; i++) {
    initializeElement(Paths::BOMB_PATH);
  }
}

PanelElement<Bomb::BombType>::Ptr
BombPanel::createElement(const std::string &path) {
  auto index =
      std::find_if(Bomb::bomb_names.begin(), Bomb::bomb_names.end(),
                   [&path](auto &pair) { return pair.second == path; });
  return BombElement::create(components.window, index->first);
}

void BombPanel::initialize() { ElementPanel<Bomb::BombType>::initialize(600); }

HeartPanel::HeartPanel(MainGameComponents &components_)
    : ElementPanel<PanelElementsTypes::HeartType>(components_) {
  direction = Direction::RIGHT;
}

void HeartPanel::createElements() {
  for (int i = 0; i < basic_elements_number; i++) {
    initializeElement(Paths::RED_HEART_PATH);
  }
}

PanelElement<PanelElementsTypes::HeartType>::Ptr
HeartPanel::createElement(const std::string &path) {
  return HeartElement::create(components.window, path);
}

void HeartPanel::initialize() {
  ElementPanel<PanelElementsTypes::HeartType>::initialize(100);
}
void HeartPanel::switchOnNextElement(){
  ElementPanel<PanelElementsTypes::HeartType>::switchOnNextElement();
  if (getElementsSize()>basic_elements_number){
    removeElement();
  }
}

template <typename T> void ElementPanel<T>::setPosition(int y, int x) {
  setPosition(tgui::Layout2d(x, y));
}

void HeartPanel::addNewElement() { addNewElement(Paths::RED_HEART_PATH); }
void BombPanel::addNewElement() {
  addNewElement(Bomb::bomb_names.at(getCurrentType()));
}
