#pragma once

#include "../../game/main_game_components/main_game_components.h"
#include "../../picture/picture.h"
#include "../bomb/bomb.h"
#include "down_panel_elements.h"
#include <iterator>

// namespace PanelElementsTypes {
// enum class HeartType { RED, GREY };
// }

// template <typename T> class PanelElement : public CustomPicture {
// public:
//   using Ptr = std::shared_ptr<PanelElement>;
//   void changeType();
//   PanelElement(const sf::RenderWindow &window, const std::string &path);
//   virtual int convertTypeToIndex() const = 0;
//   virtual T convertIndexToType(int index) const = 0;
//   T getType() const;

//   bool isOn() const;
//   bool isOff() const;

//   virtual void setOn() = 0;
//   virtual void setOff() = 0;

// protected:
//   virtual void changeStyle() = 0;
//   T current_type;

//   bool status = true;
// };

// class HeartElement : public PanelElement<PanelElementsTypes::HeartType> {
// public:
//   using Ptr = std::shared_ptr<HeartElement>;
//   HeartElement(const sf::RenderWindow &window, const std::string &path);

//   static std::map<PanelElementsTypes::HeartType, int> index_map;
//   int convertTypeToIndex() const;

//   PanelElementsTypes::HeartType convertIndexToType(int index) const;

//   // decltype(auto) getFirstOnElement();

//   static Ptr create(const sf::RenderWindow &window, const std::string &path);
//   void setOn();
//   void setOff();

// private:
//   void changeStyle();
// };

// class BombElement : public PanelElement<Bomb::BombType> {
// public:
//   using Ptr = std::shared_ptr<BombElement>;
//   BombElement(const sf::RenderWindow &window, const std::string &path);
//   int convertTypeToIndex() const;
//   Bomb::BombType convertIndexToType(int index) const;
//   static Ptr create(const sf::RenderWindow &window, const std::string &path);

//   void setOn();
//   void setOff();

// private:
//   void changeStyle();
// };

// class Heart : public CustomPicture {
// public: // dzialac na typie wewnatrz jako metode zwracajaca zrobic jakas
//         // indeksowa tam jakos zrobic wirtualna metode ktora bedzie dzialac a
//         // indeksy sie zamieni wyzej
//   using Ptr = std::shared_ptr<Heart>;
//   enum class Type { RED, GREY };
//   Type getType() const { return type; }
//   void changeType() {
//     type = type == Type::RED ? Type::GREY : Type::RED;
//     if (type == Type::RED) {
//     } else {
//     }
//     changeStyle();
//   }
//   Heart(const sf::RenderWindow &window, const std::string &path)
//       : CustomPicture(window, path) {}

//   static Ptr create(const sf::RenderWindow &window, const std::string &path)
//   {
//     return std::make_shared<Heart>(window, path);
//   }

// private:
//   void changeStyle() {
//     type == Type::GREY ? setPicture(Paths::GREY_HEART_PATH)
//                        : setPicture(Paths::RED_HEART_PATH);
//   }
//   Type type = Type::RED;
// };

template <typename T> class ElementPanel {
protected:
  using Scaler = BoxData::ScaleMenager;
  MainGameComponents &components;
  CustomPicture::Ptr panel;
  int elements_number;
  std::vector<typename PanelElement<T>::Ptr> elements;

public:
  ElementPanel(MainGameComponents &components_);
  decltype(auto) getFirstElementOn();
  decltype(auto) getFirstElementOn() const;

  int getActiveElementNumber() const;
  void removeElement();
  void addNewElement(const std::string &path);
  virtual void switchOnNextElement();
  virtual void switchOnPreviousElement();
  T getCurrentType() const;
  void changeCurrentElement();

  void setSize();
  void setPosition(int y, int x);

protected:
  virtual void initialize(int x_position);

public:
  typename PanelElement<T>::Ptr initializeElement(const std::string &path);

  virtual typename PanelElement<T>::Ptr
  createElement(const std::string &path) = 0;

  virtual void createElements() = 0;
  void remove();
};

class BombPanel : public ElementPanel<Bomb::BombType> {
public:
  BombPanel(MainGameComponents &components_);

  // virtual void switchOnNextElement() {
  //   // elements.at(element_active)->getRenderer()->setOpacity(0.75);
  //   ElementPanel::switchOnNextElement();
  // }
  // virtual void switchOnPreviousElement() {
  //   // elements.at(element_active)->getRenderer()->setOpacity(0.75);
  //   ElementPanel::switchOnPreviousElement();
  //   // elements.at(element_active)->getRenderer()->setOpacity(1);
  // }

  void createElements();
  PanelElement<Bomb::BombType>::Ptr createElement(const std::string &path);

  void initialize();
};

class HeartPanel : public ElementPanel<PanelElementsTypes::HeartType> {
public:
  HeartPanel(MainGameComponents &components_);

  // virtual void switchOnNextElement() {
  //   changeCurrentElement();
  //   ElementPanel::switchOnNextElement();
  // }
  // virtual void switchOnPreviousElement() {
  //   // changeCurrentElement();
  //   ElementPanel::switchOnPreviousElement();
  //   changeCurrentElement();
  // }
  void createElements();
  PanelElement<PanelElementsTypes::HeartType>::Ptr
  createElement(const std::string &path);
  void initialize();

  void addHeart();
};

// class DownPanel {
// private:
//   using Scaler = BoxData::ScaleMenager;
//   MainGameComponents &components;
//   CustomPicture::Ptr hearts_panel;
//   std::vector<Heart::Ptr> hearts;
//   CustomPicture::Ptr current_bomb;
//   int active_hearts;

//   void setHeartsPosition(int x, int y);

//   void createHearts(int hearts_number);
//   Heart::Ptr createHeart();
//   void changeHeartStatus(int index);

//   bool isHeartNumberValid(int number);

// public:
//   DownPanel(MainGameComponents &components_);

//   void setSize();
//   void setPosition(int y);
//   void initialize();
//   void setBomb(Bomb::BombType bomb_type);
//   void remove();
//   void addHeart();
//   void removeHeart();
//   const int getHeartNumber() const;
// };