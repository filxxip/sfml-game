#pragma once

#include "../../game/main_game_components/main_game_components.h"
#include "../../picture/picture.h"
#include "../bomb/bomb.h"
#include "down_panel_elements.h"
#include <iterator>

template <typename T> class ElementPanel {
protected:
  using Scaler = BoxData::ScaleMenager;
  MainGameComponents &components;
  CustomPicture::Ptr panel;
  int basic_elements_number;
  std::vector<typename PanelElement<T>::Ptr> elements;

public:
  enum class Direction { RIGHT, LEFT };
  ElementPanel(MainGameComponents &components_);
  decltype(auto) getFirstElementOn();
  decltype(auto) getFirstElementOn() const;

  int getActiveElementNumber() const;
  void removeElement();

  virtual void switchOnNextElement();
  virtual void switchOnPreviousElement();

  T getCurrentType() const;
  bool isAnyElementOn() const;
  void changeCurrentElement();
  void updateCurrentElement();
  void changeEveryElement();

  void setSize();
  void setPosition(int y, int x);
  void setPosition(tgui::Layout2d && layout);

protected:
  tgui::Layout2d createNewPositionAfterAdding();
  tgui::Layout2d createNewPositionAfterRemoving();
  virtual void addNewElement(const std::string &path);
  Direction direction;
  virtual void initialize(int x_position);

  int getElementsSize() const { return elements.size(); }

public:
  typename PanelElement<T>::Ptr initializeElement(const std::string &path);

  virtual typename PanelElement<T>::Ptr
  createElement(const std::string &path) = 0;

  virtual void createElements() = 0;
  void remove();
};

class BombPanel : public ElementPanel<Bomb::BombType> {
  using ElementPanel<Bomb::BombType>::addNewElement;

public:
  BombPanel(MainGameComponents &components_);

  void createElements();
  PanelElement<Bomb::BombType>::Ptr createElement(const std::string &path);

  void initialize();
  void addNewElement();
};

class HeartPanel : public ElementPanel<PanelElementsTypes::HeartType> {
  using ElementPanel<PanelElementsTypes::HeartType>::addNewElement;

public:
  HeartPanel(MainGameComponents &components_);

  void createElements();
  PanelElement<PanelElementsTypes::HeartType>::Ptr
  createElement(const std::string &path);
  void initialize();
 void switchOnNextElement();
  void addNewElement();
};
