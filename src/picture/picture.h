#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/Widgets/Picture.hpp>

class CustomPicture : public tgui::Picture {
public:
  using Ptr = std::shared_ptr<CustomPicture>;
  CustomPicture(const std::string &path);
  void setPicture(const std::string &path);
  void setMiddle(const sf::RenderWindow &window,
                 tgui::Vector2f &&delta_moved = tgui::Vector2f(0, 0));

  static Ptr create(const std::string &path);

  const bool isMiddle() const;

private:
  bool is_middled = false;
};