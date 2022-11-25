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
  std::cout << BoxData::ScaleMenager::getBombSize() << std::endl;
  picture->setSize({BoxData::ScaleMenager::getBombSize(),
                    BoxData::ScaleMenager::getBombSize()});
}

void Bomb::putUnder(CustomPicture::Ptr widget) {
  picture->setMiddlePosition(widget);
  components.addOver(picture, std::move(widget));
}

void Bomb::execute() {
  executed = true;
  destroyFromGUI();
}

void Bomb::destroyFromGUI() { components.gui.remove(picture); }