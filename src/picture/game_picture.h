#pragma once
#include "picture.h"

class GamePicture : public CustomPicture {
public:
  using Ptr = std::shared_ptr<GamePicture>;
  GamePicture(const sf::RenderWindow &window_, const std::string &path);
  static Ptr create(const sf::RenderWindow &window_, const std::string &path);

  bool isWidgetInside(const tgui::Layout2d &position,
                      const tgui::Layout2d &size) const;
};
