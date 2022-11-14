#include "down_panel.h"
#include "../../../data/config_file.h"

DownPanel::DownPanel(MainGameComponents &components_)
    : components(components_), hearts_panel(CustomPicture::create(
                                   components.window, Paths::HEART_PANEL_PATH)),
      current_bomb(CustomPicture::create(components.window, Paths::BOMB_PATH)) {

  for (int i = 0; i < 3; i++) {
    auto heart =
        CustomPicture::create(components.window, Paths::RED_HEART_PATH);
    heart->setSize(30, 30);
    hearts.push_back(std::move(heart));
  }
  hearts_panel->setSize(150, 50);
  current_bomb->setSize(50, 50);
}

void DownPanel::setPosition(int y) {
  setHeartsPosition(100, y);
  current_bomb->setPosition(components.window.getSize().x - 150, y);
}

void DownPanel::setHeartsPosition(int x, int y) {
  hearts_panel->setPosition(x, y);
  int first_pos = x + 20;
  for (auto &heart : hearts) {
    heart->setPosition(first_pos, y + 10);
    first_pos += 40;
  }
}

void DownPanel::initialize() {
  components.gui.add(current_bomb);
  components.gui.add(hearts_panel);
  components.gui.add(hearts.at(0));
  components.gui.add(hearts.at(1));
  components.gui.add(hearts.at(2));
}

void DownPanel::remove() {
  components.gui.remove(current_bomb);
  components.gui.remove(hearts_panel);
  components.gui.remove(hearts.at(0));
  components.gui.remove(hearts.at(1));
  components.gui.remove(hearts.at(2));
}

void DownPanel::setBomb(Bomb::BombType bomb_type) {
  current_bomb->setPicture(Bomb::bomb_names.at(bomb_type));
}