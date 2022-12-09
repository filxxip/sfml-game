#include "config_file.h"

BoxData::SizeOptions BoxData::ScaleMenager::option =
    BoxData::SizeOptions::NORMAL;

std::unordered_map<BoxData::ScaleMenager::PanelElement, double>
    BoxData::ScaleMenager::default_panel_sizes{
        {BoxData::ScaleMenager::PanelElement::BOMB_SIZE,
         PanelData::DEFAULT_BOMB_SIZE},
        {BoxData::ScaleMenager::PanelElement::HEART_X_POSITION,
         PanelData::DEFAULT_HEART_X_POSITION},
        {BoxData::ScaleMenager::PanelElement::BOMB_SUP_POS,
         PanelData::DEFAULT_BOMB_SUP_POS},
        {BoxData::ScaleMenager::PanelElement::HEARTS_MARGIN,
         PanelData::DEFAULT_HEARTS_MARGIN},
        {BoxData::ScaleMenager::PanelElement::HEARTS_SPACING,
         PanelData::DEFAULT_HEARTS_SPACING},
        {BoxData::ScaleMenager::PanelElement::
             DEFAULT_DELTA_PANEL_Y_POSITION_HEIGHT,
         PanelData::DEFAULT_DELTA_PANEL_Y_POSITION_HEIGHT},
        {BoxData::ScaleMenager::PanelElement::DELTA_PANEL_Y_POSITION_HEIGHT,
         PanelData::DELTA_PANEL_Y_POSITION},
        {BoxData::ScaleMenager::PanelElement::HEARTS_SIZE,
         PanelData::DEFAULT_HEARTS_SIZE},
    };

double BoxData::ScaleMenager::getBoxSize() {
  return SIZE / size_index_map.at(option);
}

int BoxData::ScaleMenager::getElementsXNumber() {
  return static_cast<int>((WindowData::WIDTH) / getBoxSize());
}
int BoxData::ScaleMenager::getElementsYNumber() {
  return static_cast<int>(
      (WindowData::HEIGHT -
       getPanelElementSize(BoxData::ScaleMenager::PanelElement::
                               DEFAULT_DELTA_PANEL_Y_POSITION_HEIGHT)) /
      getBoxSize());
}
double BoxData::ScaleMenager::getBreakSpaceX() {
  return (WindowData::WIDTH - getElementsXNumber() * getBoxSize()) /
         static_cast<double>(getElementsXNumber() - 1);
}
double BoxData::ScaleMenager::getBreakSpaceY() {
  return (WindowData::HEIGHT -
          getPanelElementSize(BoxData::ScaleMenager::PanelElement::
                                  DEFAULT_DELTA_PANEL_Y_POSITION_HEIGHT) -
          getElementsYNumber() * getBoxSize()) /
         static_cast<double>(getElementsYNumber() - 1);
}

double BoxData::ScaleMenager::getIndexBoxWidth() {
  return getBoxSize() + getBreakSpaceX();
}
double BoxData::ScaleMenager::getIndexBoxHeight() {
  return getBoxSize() + getBreakSpaceY();
}

double BoxData::ScaleMenager::getMaxXIndex() {
  return getElementsXNumber() - 2;
}
double BoxData::ScaleMenager::getMaxYIndex() {
  return getElementsYNumber() - 2;
}

double BoxData::ScaleMenager::getMinXIndex() { return 1; }
double BoxData::ScaleMenager::getMinYIndex() { return 1; }

double BoxData::ScaleMenager::getPlayerSize() { return getBoxSize() * 0.9; }

void BoxData::ScaleMenager::changeOption(SizeOptions option_) {
  option = option_;
}
int BoxData::ScaleMenager::getStonesElementsNumber() {
  return static_cast<int>(getElementsNumber() * 0.3);
}
int BoxData::ScaleMenager::getBoxesElementsNumber() {
  return static_cast<int>(getElementsNumber() * 0.7);
}

int BoxData::ScaleMenager::getElementsNumber() {
  return static_cast<int>(DEFAULT_ELEMENTS_NUMBER * size_index_map.at(option) *
                          size_index_map.at(option));
}

double BoxData::ScaleMenager::getBombSize() { return getPlayerSize() * 0.9; }

double BoxData::ScaleMenager::getPanelElementSize(
    BoxData::ScaleMenager::PanelElement element_type) {
  if (option == BoxData::SizeOptions::AVERAGE ||
      option == BoxData::SizeOptions::MINIMUM ||
      option == BoxData::SizeOptions::NORMAL) {
    return default_panel_sizes.at(element_type) *
           size_index_map.at(BoxData::SizeOptions::NORMAL);
  }
  return default_panel_sizes.at(element_type) / 0.5 / size_index_map.at(option);
}
