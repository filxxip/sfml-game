#include "position_widget_menager.h"
#include "../menu/main_menu/main_menu_layout/main_menu_layout.h"
#include "../message_box/message_box.h"
#include "../picture/picture.h"

template <typename T>
void PositionWidgetMenager::setMiddle(const sf::RenderWindow &window,
                                      const std::shared_ptr<T> &widget,
                                      const sf::Vector2f &moved_vector) {
  const auto [width, height] = window.getSize();
  const auto [message_width, message_height] = widget->getSize();
  widget->setPosition((width - message_width) / 2 + moved_vector.x,
                      (height - message_height) / 2 + moved_vector.y);
}

// template <typename T>
// void PositionWidgetMenager::keepPosition(const sf::RenderWindow &window,
//                                          const std::shared_ptr<T> &widget) {
//   auto [window_width, window_height] = window.getSize();
//   std::cout << "1" << std::endl;
//   auto ratio_data = widget->getRatioData();
//   std::cout << "2" << std::endl;
//   widget->setSize(ratio_data.width_ratio * window_width,
//                   ratio_data.height_ratio * window_height);
//   std::cout << "3" << std::endl;
//   widget->setPosition(ratio_data.x_position_ratio * window_width,
//                       ratio_data.y_position_ratio * window_height);
//   std::cout << "4" << std::endl;
// }

// template void PositionWidgetMenager::keepPosition(
//     const sf::RenderWindow &window,
//     const std::shared_ptr<CustomPicture> &widget);

// template void PositionWidgetMenager::keepPosition(
//     const sf::RenderWindow &window,
//     const std::shared_ptr<MainMenuLayout> &widget);

template void
PositionWidgetMenager::setMiddle(const sf::RenderWindow &window,
                                 const std::shared_ptr<CustomPicture> &widget,
                                 const sf::Vector2f &moved_vector);

template void
PositionWidgetMenager::setMiddle(const sf::RenderWindow &window,
                                 const std::shared_ptr<MainMenuLayout> &widget,
                                 const sf::Vector2f &moved_vector);

// template void PositionWidgetMenager::keepPosition(
//     const sf::RenderWindow &window,
//     const std::shared_ptr<CustomMessageBox> &widget);

template void PositionWidgetMenager::setMiddle(
    const sf::RenderWindow &window,
    const std::shared_ptr<CustomMessageBox> &widget,
    const sf::Vector2f &moved_vector);