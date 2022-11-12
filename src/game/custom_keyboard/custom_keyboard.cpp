#include "custom_keyboard.h"
#include "../../../data/config_file.h"
#include <thread>

CustomKeyboard::CustomKeyboard() {
  for (auto key_index = 0;
       key_index <= static_cast<int>(sf::Keyboard::KeyCount); key_index++) {
    auto key = static_cast<sf::Keyboard::Key>(key_index);
    clickedStatus.emplace(std::make_pair(key, false));
  }
}

const bool CustomKeyboard::isClicked(sf::Keyboard::Key key) const {
  return clickedStatus.at(key);
}

const bool CustomKeyboard::isNotClicked(sf::Keyboard::Key key) const {
  return !clickedStatus.at(key);
}

void CustomKeyboard::setClicked(sf::Keyboard::Key key) {
  clickedStatus.at(key) = true;
}

void CustomKeyboard::setClickedWithThreadDelay(sf::Keyboard::Key key,
                                               const int miliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
  setClicked(key);
}

void CustomKeyboard::setNotClickedWithThreadDelay(sf::Keyboard::Key key,
                                                  const int miliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
  setNotClicked(key);
}

void CustomKeyboard::setClickedAfterDelay(sf::Keyboard::Key key) {
  std::thread t1(&CustomKeyboard::setClickedWithThreadDelay, this, key,
                 KeyboardData::THREAD_TIME);
  t1.detach();
}

void CustomKeyboard::setNotClickedAfterDelay(sf::Keyboard::Key key) {
  std::thread t1(&CustomKeyboard::setNotClickedWithThreadDelay, this, key,
                 KeyboardData::THREAD_TIME);
  t1.detach();
}

void CustomKeyboard::setNotClicked(sf::Keyboard::Key key) {
  clickedStatus.at(key) = false;
}

const bool CustomKeyboard::wasClickedYet(sf::Keyboard::Key key) {
  return sf::Keyboard::isKeyPressed(key) && isNotClicked(key);
}

void CustomKeyboard::clickAndUnclickKey(sf::Keyboard::Key key) {
  setClicked(key);
  setNotClickedAfterDelay(key);
}