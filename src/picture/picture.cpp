#include "picture.h"

CustomPicture::CustomPicture(const sf::RenderWindow &window_,
                             const std::string &path) {
  // nSizeChange([this]() { ratio_data.setSizeRatios(getSize()); });
  // onPositionChange([this]() { ratio_data.setPositionRatios(getPosition());
  // });
  setPicture(path);
}

void CustomPicture::setPicture(const std::string &path) {
  auto texture = tgui::Texture(path);
  getRenderer()->setTexture(texture);
}

CustomPicture::Ptr CustomPicture::create(const sf::RenderWindow &window_,
                                         const std::string &path) {
  return std::make_shared<CustomPicture>(window_, path);
}

// const RatioWidgetData &CustomPicture::getRatioData() const {
//   return ratio_data;
// }
// void CustomPicture::setRatioData() { ratio_data.set(getSize(),
// getPosition()); }
