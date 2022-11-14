#include "bomb.h"
#include "../../../data/config_file.h"

const std::unordered_map<Bomb::BombType, std::string> Bomb::bomb_names{
    {Bomb::BombType::TIME, Paths::BOMB_PATH},
    {Bomb::BombType::CLICK, Paths::CLICK_BOMB_PATH},
    {Bomb::BombType::HEART, Paths::HEART_BOMB_PATH},
    {Bomb::BombType::MYSTERY, Paths::MYSTERY_BOMB_PATH},
};

Bomb::Bomb(MainGameComponents &components_)
    : components(components_),
      picture(CustomPicture::create(components.window, Paths::BOMB_PATH)) {
  picture->setSize({30, 30});
}

void Bomb::putUnder(tgui::Widget::Ptr widget) {
  auto [width, height] = widget->getSize();
  auto [x, y] = widget->getPosition();
  auto [pct_width, pct_height] = picture->getSize();
  auto new_x = x + 0.5 * width - 0.5 * pct_width;
  auto new_y = y + 0.5 * height - 0.5 * pct_height;
  picture->setPosition(new_x, new_y);
  components.addOver(picture, std::move(widget));
}

void Bomb::execute() {
  executed = true;
  destroyFromGUI();
}

void Bomb::destroyFromGUI() { components.gui.remove(picture); }