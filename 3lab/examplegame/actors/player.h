#pragma once
#include <map>

#include "actors/human.h"

using std::map;

namespace lab3 {

  class Player : public Human {
    Inputer::command_t last_command;

    static const map<string, Inputer::validation_result_t (Player::*) (const Inputer::command_t& command) const> TOP_COMMAND_VALIDATORS;

  public:
    Player(const WorldCoord& initial_position) : Human(initial_position, "You") {}

    Inputer::validation_result_t validate_command(const Inputer::command_t& command) const;

  protected:
    virtual void input(Game& input) override;

  private:
    Inputer::validation_result_t commands_help(const Inputer::command_t& command) const;
    Inputer::validation_result_t validate_command_directional(const Inputer::command_t& command) const;

  };

}
