#pragma once

#include <cstdlib>

#include <chrono>

class Timer {
private:
  using time = std::chrono::_V2::steady_clock;
  std::chrono::_V2::steady_clock::time_point last_measure;
  int lasts;
  bool timer_is_running = false;

public:
  Timer();

  void measure(bool is_game_running);
  int getLasts() const;
  void run() {
    last_measure = time::now();
    timer_is_running = true;
  }
  void stop() { timer_is_running = false; }
};