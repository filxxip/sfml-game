#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/Widgets/Picture.hpp>

#include "../position_widget_menager/position_widget_menager.h"

class CustomPicture : public tgui::Picture {
public:
  using Ptr = std::shared_ptr<CustomPicture>;
  CustomPicture(const sf::RenderWindow &window_, const std::string &path);
  void setPicture(const std::string &path);

  static Ptr create(const sf::RenderWindow &window_, const std::string &path);

  const RatioWidgetData &getRatioData() const;
  void setRatioData();

private:
  RatioWidgetData ratio_data;
};