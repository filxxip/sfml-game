#include "down_panel.h"
#include "../../../data/config_file.h"

DownPanel::DownPanel(MainGameComponents &components_)
    : components(components_), hearts_panel(CustomPicture::create(
                                   components.window, Paths::HEART_PANEL_PATH)),
      current_bomb(CustomPicture::create(components.window, Paths::BOMB_PATH)) {

}

void DownPanel::removeHeart() {
  if (active_hearts != 0) {
    hearts.at(active_hearts - 1)->changeType();
    active_hearts--;
  }
}

void DownPanel::addHeart() {
  if (active_hearts == hearts.size()) {
    if (isHeartNumberValid(hearts.size() + 1)) {
      auto heart = createHeart();
      components.gui.add(heart);
      setSize();
      setPosition(components.window.getSize().y -
                  Scaler::getPanelElementSize(
                      Scaler::PanelElement::DELTA_PANEL_Y_POSITION_HEIGHT));
      active_hearts++;
    }
  } else {
    hearts.at(active_hearts)->changeType();
    active_hearts++;
  }
}

void DownPanel::changeHeartStatus(int index) { hearts.at(index)->changeType(); }

void DownPanel::setPosition(int y) {
  setHeartsPosition(
      Scaler::getPanelElementSize(Scaler::PanelElement::HEART_X_POSITION), y);
  current_bomb->setPosition(
      components.window.getSize().x -
          Scaler::getPanelElementSize(Scaler::PanelElement::BOMB_SUP_POS),
      y);
}

void DownPanel::setSize() {
  hearts_panel->setSize(
      hearts.size() *
              Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE) +
          2 * Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_MARGIN) +
          (hearts.size() - 1) *
              Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SPACING),
      Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE) +
          2 * Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_MARGIN));
  current_bomb->setSize(
      Scaler::getPanelElementSize(Scaler::PanelElement::BOMB_SIZE),
      Scaler::getPanelElementSize(Scaler::PanelElement::BOMB_SIZE));
}

void DownPanel::setHeartsPosition(int x, int y) {
  hearts_panel->setPosition(x, y);
  int first_pos =
      x + Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_MARGIN);
  for (auto &heart : hearts) {
    heart->setPosition(first_pos, y + Scaler::getPanelElementSize(
                                          Scaler::PanelElement::HEARTS_MARGIN));
    first_pos +=
        Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SPACING) +
        Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE);
  }
}
Heart::Ptr DownPanel::createHeart() {
  auto heart = Heart::create(components.window, Paths::RED_HEART_PATH);
  heart->setSize(
      Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE),
      Scaler::getPanelElementSize(Scaler::PanelElement::HEARTS_SIZE));
  hearts.push_back(heart);
  return heart;
}

bool DownPanel::isHeartNumberValid(int number) {
  return number <= 10 && number > 0;
}

void DownPanel::createHearts(int hearts_number) {
  if (!isHeartNumberValid(hearts_number)) {
    hearts_number = PanelData::DEFAULT_HEART_NUMBER;
  }
  for (int i = 0; i < hearts_number; i++) {
    createHeart();
  }
}

void DownPanel::initialize() {
  components.gui.add(
      current_bomb); // chyba lepiej bez constexpr ogarne funckje z template i
                     // potem using i po prostu wywolywac dana funckje i tyle,
                     // tworzenie tyych wszystich templatowanych funckji pewnie
                     // i tak wiecej czasu zajmie niz szybkie w miare obliczenie
                     // rozmiaru
  components.gui.add(hearts_panel);
  active_hearts = PanelData::DEFAULT_HEART_NUMBER;
  createHearts(active_hearts);
  setPosition(components.window.getSize().y -
              Scaler::getPanelElementSize(
                  Scaler::PanelElement::DELTA_PANEL_Y_POSITION_HEIGHT));
  setSize();
  for (auto &heart : hearts) {
    components.gui.add(heart);
  }
}

void DownPanel::remove() {
  components.gui.remove(current_bomb);
  components.gui.remove(hearts_panel);
  for (auto &heart : hearts) {
    components.gui.remove(heart);
  }
  hearts.clear();
}

void DownPanel::setBomb(Bomb::BombType bomb_type) {
  current_bomb->setPicture(Bomb::bomb_names.at(bomb_type));
}

const int DownPanel::getHeartNumber() const { return active_hearts; }