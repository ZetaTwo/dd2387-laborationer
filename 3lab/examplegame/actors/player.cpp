#include <map>

#include "player.h"
#include "game.h"
#include "util.h"

using std::find;
using std::map;

namespace lab3 {

  const map<string, direction_t> DIRECTION_COMMANDS = {
    { "u", DIR_NORTH },
    { "r", DIR_EAST },
    { "d", DIR_SOUTH },
    { "l", DIR_WEST }
  };

  const map<string, Inputer::validation_result_t (Player::*) (const Inputer::command_t& subcommand) const> TOP_COMMANDS = {
    { "g", &Player::validate_subcommand_move },
    { "go", &Player::validate_subcommand_move },
    { "m", &Player::validate_subcommand_move },
    { "move", &Player::validate_subcommand_move },
  };

  void Player::input(Game& game) {
    last_command = game.get_inputer().get_input(game, *this);
  }

  Inputer::validation_result_t Player::validate_command(const Inputer::command_t& command) const {
    if(command.size() == 0) {
      return { false, "Empty command" };
    }

    if(command[0] == "help") {
      return { false, "Commands:\ng (u | d | l | r) : Move up, down, left, right respectively" };
    }

    auto validator_it = TOP_COMMANDS.find(command[0]);
    if(validator_it != TOP_COMMANDS.end()) {
      return (this->*(validator_it->second))(command);
    }

    if(command[0] == "g") {
    }

    return { false, "Unrecognized command." };
  }

  Inputer::validation_result_t Player::validate_subcommand_move(const Inputer::command_t& command) const {
    if(command.size() > 1) {
      if(DIRECTION_COMMANDS.count(command[1]) > 0) {
        return { true, "" };
      }
      return { false, "Invalid direction." };
    }
    return { false, "No direction specified." };
  }

}
