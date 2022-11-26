#include "timer.h"
#include "utility"

Timer::Timer() : last_measure(time::now()), lasts(0) {}

void Timer::measure(bool is_game_running) {
  auto now = time::now();
  if (is_game_running && timer_is_running) {
    lasts += std::chrono::duration_cast<std::chrono::milliseconds>(now -
                                                                   last_measure)
                 .count();
  }
  last_measure = std::move(now);
}
int Timer::getLasts() const { return lasts; }