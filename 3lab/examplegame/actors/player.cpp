#include <map>
#include <ostream>

#include "player.h"
#include "game.h"
#include "util.h"

using std::endl;
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
    { "a", &Player::validate_subcommand_directional },
    { "activate", &Player::validate_subcommand_directional },
    { "g", &Player::validate_subcommand_directional },
    { "go", &Player::validate_subcommand_directional },
    { "m", &Player::validate_subcommand_directional },
    { "move", &Player::validate_subcommand_directional },
    { "help", &Player::commands_help }
  };

  const map<string, string> COMMANDS_HELP = {
    { "move", "move (u | d | l | r)\nMove up, down, left, right respectively\nAliases: g, go, m" },
    { "activate", "activate (u | d | l | r)\nActivate something above, below, left, right respectively\nAliases: a" }
  };

  void Player::input(Game& game) {
    last_command = game.get_inputer().get_input(game, *this);
  }

  Inputer::validation_result_t Player::commands_help(const Inputer::command_t& command) const {
    if(command.size() > 1) {
      auto help_it = COMMANDS_HELP.find(command[1]);
      if(help_it != COMMANDS_HELP.end()) {
        return { false, help_it->second };
      } else {
        return { false, "Unrecognized subcommand." };
      }
    }

    stringstream commands;
    commands << "Commands:" << endl;
    for(const pair<string, string>& help : COMMANDS_HELP) {
      commands << endl << help.first;
    }
    return { false, commands.str() };
  }

  Inputer::validation_result_t Player::validate_command(const Inputer::command_t& command) const {
    if(command.size() == 0) {
      return { false, "Empty command" };
    }

    auto validator_it = TOP_COMMANDS.find(command[0]);
    if(validator_it != TOP_COMMANDS.end()) {
      return (this->*(validator_it->second))(command);
    }

    if(command[0] == "g") {
    }

    return { false, "Unrecognized command." };
  }

  Inputer::validation_result_t Player::validate_subcommand_directional(const Inputer::command_t& command) const {
    if(command.size() > 1) {
      if(DIRECTION_COMMANDS.count(command[1]) > 0) {
        return { true, "" };
      }
      return { false, "Invalid direction." };
    }
    return { false, "No direction specified." };
  }

}
