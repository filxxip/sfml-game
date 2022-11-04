#include "position_widget_menager.h"
#include "../menu/main_menu/main_menu_layout/main_menu_layout.h"
#include "../picture/picture.h"

template <typename T>
void PositionWidgetMenager::setMiddle(const sf::RenderWindow &window,
                                      const std::shared_ptr<T> &widget,
                                      const sf::Vector2f &moved_vector) {
  const auto [width, height] = window.getSize();
  const auto [message_width, message_height] = widget->getSize();
  widget->setPosition((width - message_width) / 2 + moved_vector.x,
                      (height - message_height) / 2 + moved_vector.y);

  widget->setRatioData();
}

template <typename T>
void PositionWidgetMenager::keepPosition(const sf::RenderWindow &window,
                                         const std::shared_ptr<T> &widget) {
  auto [window_width, window_height] = window.getSize();
  auto ratio_data = widget->getRatioData();
  widget->setSize(ratio_data.width_ratio * window_width,
                  ratio_data.height_ratio * window_height);
  widget->setPosition(ratio_data.x_position_ratio * window_width,
                      ratio_data.y_position_ratio * window_height);
}

template void PositionWidgetMenager::keepPosition(
    const sf::RenderWindow &window,
    const std::shared_ptr<CustomPicture> &widget);

template void PositionWidgetMenager::keepPosition(
    const sf::RenderWindow &window,
    const std::shared_ptr<MainMenuLayout> &widget);

template void
PositionWidgetMenager::setMiddle(const sf::RenderWindow &window,
                                 const std::shared_ptr<CustomPicture> &widget,
                                 const sf::Vector2f &moved_vector);

template void
PositionWidgetMenager::setMiddle(const sf::RenderWindow &window,
                                 const std::shared_ptr<MainMenuLayout> &widget,
                                 const sf::Vector2f &moved_vector);