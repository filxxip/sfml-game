#pragma once

#include "../standard_time_bomb.h"

class HeartBomb : public StandardTimeBomb {
public:
  using Ptr = std::unique_ptr<HeartBomb>;
  HeartBomb(MainGameComponents &components_);
  static HeartBomb::Ptr create(MainGameComponents &components) {
    return std::make_unique<HeartBomb>(components);
  }
  bool affectOnPlayer()const override{return false;}
};