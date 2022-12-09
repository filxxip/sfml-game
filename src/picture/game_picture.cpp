#include "game_picture.h"

GamePicture::GamePicture(MainGameComponents &components_,
                         const std::string &path)
    : components(components_), CustomPicture(components_.window, path) {}

GamePicture::Ptr GamePicture::create(MainGameComponents &components_,
                                     const std::string &path) {
  return std::make_shared<GamePicture>(components_, path);
}

bool GamePicture::isWidgetInside(const tgui::Layout2d &position,
                                 const tgui::Layout2d &size) const {
  auto x_left = getPosition().x;
  auto x_right = x_left + getSize().x;
  auto y_up = getPosition().y;
  auto y_down = y_up + getSize().y;

  auto x_left2 = position.x.getValue();
  auto x_right2 = x_left2 + size.x.getValue();
  auto y_up2 = position.y.getValue();
  auto y_down2 = y_up2 + size.y.getValue();

  if (x_left2 >= x_right || x_left >= x_right2) {
    return false;
  }
  if (y_down2 <= y_up) {
    return false;
  }
  if (y_down <= y_up2) {
    return false;
  }
  return true;
}
void GamePicture::setIndexPosition(Index &&index) {
  setPosition(index.convertToPosition(getSize().x, getSize().y));
}

Index GamePicture::getIndexPosition() {
  return Index::getIndexFromPosition(getSize(), getPosition());
}

const std::unordered_map<BonusItem::Type, std::string> BonusItem::types_paths{
    {BonusItem::Type::CLICK_BOMB, Paths::CLICK_BOMB_BONUS},
    {BonusItem::Type::HEART_BOMB, Paths::HEART_BOMB_BONUS},
    {BonusItem::Type::MYSTERY_BOMB, Paths::MYSTERY_BOMB_BONUS},
    {BonusItem::Type::NEW_BOMB, Paths::BOMB_BONUS},
    {BonusItem::Type::NEW_HEART, Paths::HEART_BONUS},
    {BonusItem::Type::PLUS_POWER, Paths::SPEED_BONUS},
    {BonusItem::Type::PLUS_TWO_POWER, Paths::DOUBLE_SPEED_BOMB_BONUS},
    {BonusItem::Type::REMOVE_RANDOM_OPP, Paths::REMOVE_BONUS},
    {BonusItem::Type::PLUS_SPEED, Paths::SHOE_BONUS}};

BonusItem::BonusItem(MainGameComponents &components_, Type type_)
    : GamePicture(components_, BonusItem::types_paths.at(type_)), type(type_), own_signal("my_custom_signal"){
  setSize({BoxData::ScaleMenager::getBoxSize(),
           BoxData::ScaleMenager::getBoxSize()});
}

BonusItem::Ptr create(MainGameComponents &components_, BonusItem::Type type_) {
  return std::make_shared<BonusItem>(components_, type_);
}
