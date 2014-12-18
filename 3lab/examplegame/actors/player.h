#pragma once
#include <map>

#include "actors/human.h"

using std::map;

namespace lab3 {

  class Player : public Human {
    Inputer::command_t last_command;

    static const map<string, Inputer::validation_result_t (Player::*) (const Inputer::command_t& command) const> TOP_COMMAND_VALIDATORS;
    static const map<string, void (Player::*) (Game& game, const Inputer::command_t& command)> TOP_COMMAND_EVALUATORS;

  public:
    Player(const WorldCoord& initial_position) : Human(initial_position, "You") {}

    Inputer::validation_result_t validate_command(const Inputer::command_t& command) const;

  protected:
    virtual void input(Game& input) override;
    virtual void do_tick(Game& game) override;

  private:
    Inputer::validation_result_t commands_help(const Inputer::command_t& command) const;
    Inputer::validation_result_t validate_command_directional(const Inputer::command_t& command) const;

    void evaluate_command_activate(Game& game, const Inputer::command_t& last_command);
    void evaluate_command_move(Game& game, const Inputer::command_t& last_command);

  };

}
