#pragma once

#include "human.h"
namespace lab3 {

  class Player : public Human {
    Player(const WorldCoord& initial_position) : Human(initial_position, "You") {}

    virtual void input(Game& input) override;
  };

}