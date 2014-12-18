#include <map>
#include <ostream>
#include <stdexcept>
#include <string>

#include "player.h"
#include "game.h"
#include "util.h"

using std::endl;
using std::find;
using std::invalid_argument;
using std::map;
using std::out_of_range;
using std::runtime_error;
using std::stoi;

namespace lab3 {

  const map<string, direction_t> DIRECTION_COMMANDS = {
    { "w", DIR_NORTH },
    { "a", DIR_WEST },
    { "s", DIR_SOUTH },
    { "d", DIR_EAST }
  };

  const map<string, Inputer::validation_result_t (Player::*) (const Inputer::command_t& command) const> Player::TOP_COMMAND_VALIDATORS = {
    { "a", &Player::validate_command_directional },
    { "activate", &Player::validate_command_directional },
    { "g", &Player::validate_command_directional },
    { "go", &Player::validate_command_directional },
    { "m", &Player::validate_command_directional },
    { "move", &Player::validate_command_directional },
    { "help", &Player::commands_help }
  };

  const map<string, void (Player::*) (Game& game, const Inputer::command_t& command)> Player::TOP_COMMAND_EVALUATORS = {
    { "a", &Player::evaluate_command_activate },
    { "activate", &Player::evaluate_command_activate },
    { "g", &Player::evaluate_command_move },
    { "go", &Player::evaluate_command_move },
    { "m", &Player::evaluate_command_move },
    { "move", &Player::evaluate_command_move }
  };

  const map<string, string> COMMANDS_HELP = {
    { "move", "move (w | a | s | d)\nMove up, left, down, right respectively\nAliases: g, go, m" },
    { "activate", "activate (w | a | s | d)\nActivate something above, left, below, right respectively\nAliases: a" }
  };

  void Player::input(Game& game) {
    if(repeat_command_times == 0 || --repeat_command_times == 0) {
      last_command = game.get_inputer().get_input(game, *this);
    }
  }

  void Player::do_tick(Game& game) {
    (this->*(TOP_COMMAND_EVALUATORS.at(last_command[0])))(game, last_command);
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

    auto validator_it = TOP_COMMAND_VALIDATORS.find(command[0]);
    if(validator_it != TOP_COMMAND_VALIDATORS.end()) {
      return (this->*(validator_it->second))(command);
    }

    if(command[0] == "g") {
    }

    return { false, "Unrecognized command." };
  }

  Inputer::validation_result_t Player::validate_command_directional(const Inputer::command_t& command) const {
    if(command.size() > 1) {
      if(DIRECTION_COMMANDS.count(command[1]) > 0) {
        if(command.size() > 2) {
          try {
            if(stoi(command[2]) < 1) {
              return { false, "Invalid distance." };
            }
          } catch(invalid_argument e) {
            return { false, "Invalid distance." };
          } catch(out_of_range e) {
            return { false, "Distance too large." };
          }
        }
        return { true, "" };
      }
      return { false, "Invalid direction." };
    }
    return { false, "No direction specified." };
  }

  void Player::evaluate_command_activate(Game& game, const Inputer::command_t& last_command) {
    throw runtime_error{"Not implemented"};
  }

  void Player::evaluate_command_move(Game& game, const Inputer::command_t& last_command) {
    if(repeat_command_times == 0 && last_command.size() > 2) {
      repeat_command_times = stoi(last_command[2]);
    }

    move(game, DIRECTION_COMMANDS.at(last_command[1]));
  }

}
