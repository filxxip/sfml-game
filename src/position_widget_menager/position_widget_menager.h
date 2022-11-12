#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/Widget.hpp>

// struct RatioWidgetData {
//   const sf::RenderWindow &window;
//   double width_ratio;
//   double height_ratio;
//   double x_position_ratio;
//   double y_position_ratio;

//   RatioWidgetData(const sf::RenderWindow &window_) : window(window_) {}

//   void setSizeRatios(const tgui::Vector2f &size) {
//     const auto [width, height] = window.getSize();
//     width_ratio = size.x / width;
//     height_ratio = size.y / height;
//   }
//   void setPositionRatios(const tgui::Vector2f &position) {
//     const auto [width, height] = window.getSize();
//     x_position_ratio = position.x / width;
//     y_position_ratio = position.y / height;
//   }

//   void set(const tgui::Vector2f &size, const tgui::Vector2f &position) {
//     setSizeRatios(size);
//     setPositionRatios(size);
//   }
// };

class PositionWidgetMenager {
public:
  // template <typename T>
  // static void keepPosition(const sf::RenderWindow &window_,
  //                          const std::shared_ptr<T> &widget);
  template <typename T>
  static void setMiddle(const sf::RenderWindow &window_,
                        const std::shared_ptr<T> &widget,
                        const sf::Vector2f &moved_vector = {0, 0});
};