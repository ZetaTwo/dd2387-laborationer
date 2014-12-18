#pragma once

#include "actors/human.h"

namespace lab3 {

  class Player : public Human {
  public:
    Player(const WorldCoord& initial_position) : Human(initial_position, "You") {}

    Inputer::validation_result_t validate_command(const Inputer::command_t& command) const;
    Inputer::validation_result_t validate_subcommand_move(const Inputer::command_t& command) const;

  protected:
    virtual void input(Game& input) override;

  private:
    Inputer::command_t last_command;
  };

}
