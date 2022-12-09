#pragma once

#include "../../game/main_game_components/main_game_components.h"
#include "../../picture/picture.h"
#include "../bomb/bomb.h"
#include <iterator>

namespace PanelElementsTypes {
enum class HeartType { RED, GREY };
}

template <typename T> class PanelElement : public CustomPicture {
public:
  using Ptr = std::shared_ptr<PanelElement<T>>;
  void changeType();
  PanelElement(const sf::RenderWindow &window, const std::string &path);
  virtual int convertTypeToIndex() const = 0;
  virtual T convertIndexToType(int index) const = 0;
  T getType() const;

  bool isOn() const;
  bool isOff() const;

  virtual void setOn() = 0;
  virtual void setOff() = 0;
  virtual void changeStyle() = 0;

protected:
  T current_type;

  bool status = true;
};

class HeartElement : public PanelElement<PanelElementsTypes::HeartType> {
public:
  using Ptr = std::shared_ptr<HeartElement>;
  HeartElement(const sf::RenderWindow &window, const std::string &path);

  static std::map<PanelElementsTypes::HeartType, int> index_map;
  int convertTypeToIndex() const;

  PanelElementsTypes::HeartType convertIndexToType(int index) const;

  static Ptr create(const sf::RenderWindow &window, const std::string &path);
  void setOn();
  void setOff();

private:
  void changeStyle();
};

class BombElement : public PanelElement<Bomb::BombType> {

public:
  using Ptr = std::shared_ptr<BombElement>;
  BombElement(const sf::RenderWindow &window, Bomb::BombType type);
  int convertTypeToIndex() const;
  Bomb::BombType convertIndexToType(int index) const;
  static Ptr create(const sf::RenderWindow &window, Bomb::BombType type);

  void setOn();
  void setOff();

  void addOption(Bomb::BombType option){
    possible_used_bombs.push_back(option);
  }

private:
  std::vector<Bomb::BombType> possible_used_bombs;
  void changeStyle();
};
