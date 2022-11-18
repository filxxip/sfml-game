#include "box.h"
#include "../../../data/config_file.h"

Box::Box(MainGameComponents &components_)
    : components(components_),
      picture(GamePicture::create(components.window, Paths::BOX_PATH)) {
  picture->setSize({BoxData::SIZE, BoxData::SIZE});
}

void Box::put(double position_x, double position_y) {
  picture->setPosition(position_x, position_y);
  components.gui.add(picture);
}

bool Box::isWidgetInside(const tgui::Layout2d &layout,
                         const tgui::Layout2d &size) const {
  return picture->isWidgetInside(layout, size);
}

GamePicture::Ptr &Box::getPicture() { return picture; }