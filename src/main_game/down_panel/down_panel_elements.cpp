#include "down_panel_elements.h"
#include "../../../data/config_file.h"

std::map<PanelElementsTypes::HeartType, int> HeartElement::index_map{
    {PanelElementsTypes::HeartType::RED, 0},
    {PanelElementsTypes::HeartType::GREY, 1}};

// std::map<Bomb::BombType, int> BombElement::index_map{
//     {Bomb::BombType::TIME, 0},
//     {Bomb::BombType::CLICK, 1},
//     {Bomb::BombType::MYSTERY, 2},
//     {Bomb::BombType::HEART, 3}};

template class PanelElement<PanelElementsTypes::HeartType>;
template class PanelElement<Bomb::BombType>;

template <typename T> void PanelElement<T>::changeType() {
  current_type = convertIndexToType(convertTypeToIndex() + 1);
  if (isOn()) {
    changeStyle();
  }
}
template <typename T>
PanelElement<T>::PanelElement(const sf::RenderWindow &window,
                              const std::string &path)
    : CustomPicture(window, path) {}

template <typename T> T PanelElement<T>::getType() const {
  return current_type;
}

template <typename T> bool PanelElement<T>::isOn() const { return status; }
template <typename T> bool PanelElement<T>::isOff() const { return !status; }

HeartElement::HeartElement(const sf::RenderWindow &window,
                           const std::string &path)
    : PanelElement(window, path) {
  current_type = PanelElementsTypes::HeartType::RED;
}

int HeartElement::convertTypeToIndex() const {
  return index_map.at(current_type);
}

PanelElementsTypes::HeartType
HeartElement::convertIndexToType(int index) const {
  auto el = std::find_if(index_map.begin(), index_map.end(),
                         [index](auto &pair) { return index == pair.second; });
  return el != index_map.end() ? el->first : PanelElementsTypes::HeartType::RED;
}

HeartElement::Ptr HeartElement::create(const sf::RenderWindow &window,
                                       const std::string &path) {
  return std::make_shared<HeartElement>(window, path);
}

void HeartElement::setOn() {
  status = true;
  current_type = PanelElementsTypes::HeartType::RED;
  changeStyle();
}

void HeartElement::setOff() {
  status = false;
  current_type = PanelElementsTypes::HeartType::GREY;
  changeStyle();
}

void HeartElement::changeStyle() {
  current_type == PanelElementsTypes::HeartType::GREY
      ? setPicture(Paths::GREY_HEART_PATH)
      : setPicture(Paths::RED_HEART_PATH);
}

BombElement::BombElement(const sf::RenderWindow &window, Bomb::BombType type)
    : PanelElement(window, Bomb::bomb_names.at(type)) {
  current_type = type;
}

int BombElement::convertTypeToIndex() const {
  auto index =
      std::find_if(Bomb::bomb_names.begin(), Bomb::bomb_names.end(),
                   [this](auto &pair) { return current_type == pair.first; });
  return std::distance(Bomb::bomb_names.begin(), std::move(index));
}

Bomb::BombType BombElement::convertIndexToType(int index) const {
  auto el = Bomb::bomb_names.begin();
  std::advance(el, index);
  return index < Bomb::bomb_names.size() ? el->first
                                         : Bomb::bomb_names.begin()->first;
}
BombElement::Ptr BombElement::create(const sf::RenderWindow &window,
                                     Bomb::BombType type) {
  return std::make_shared<BombElement>(window, type);
}

void BombElement::setOn() {
  status = true;
  getRenderer()->setOpacity(1);
}
void BombElement::setOff() {
  status = false;
  getRenderer()->setOpacity(0.5);
}

void BombElement::changeStyle() {
  std::cout << Bomb::bomb_names.at(current_type) << std::endl;
  setPicture(Bomb::bomb_names.at(current_type));
}
