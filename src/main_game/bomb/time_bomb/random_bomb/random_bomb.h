#pragma once

#include "../standard_time_bomb.h"

class RandomTimeBomb : public StandardTimeBomb {
public:
  using Ptr = std::unique_ptr<RandomTimeBomb>;
  RandomTimeBomb(MainGameComponents &components_);
  static RandomTimeBomb::Ptr create(MainGameComponents &components) {
    return std::make_unique<RandomTimeBomb>(components);
  }

private:
  void setRandomTime(int start, int end);
};