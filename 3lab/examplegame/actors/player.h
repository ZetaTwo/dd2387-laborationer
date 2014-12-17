#pragma once

#include "human.h"
namespace lab3 {

  class Player : public Human {
  public:
    Player(const WorldCoord& initial_position) : Human(initial_position, "You") {}

  protected:
    virtual void input(Game& input) override;

  private:
    Inputer::command_t last_command;
  };

}