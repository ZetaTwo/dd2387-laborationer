#include <map>
#include <ostream>
#include <stdexcept>
#include <string>

#include "player.h"
#include "game.h"
#include "util.h"

using std::bad_cast;
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
    { "i", &Player::validate_command_inventory },
    { "inventory", &Player::validate_command_inventory },
    { "m", &Player::validate_command_directional },
    { "move", &Player::validate_command_directional },
    { "help", &Player::commands_help }
  };

  const map<string, void (Player::*) (Game& game, const Inputer::command_t& command)> Player::TOP_COMMAND_EVALUATORS = {
    { "a", &Player::evaluate_command_activate },
    { "activate", &Player::evaluate_command_activate },
    { "g", &Player::evaluate_command_move },
    { "go", &Player::evaluate_command_move },
    { "i", &Player::evaluate_command_inventory },
    { "inventory", &Player::evaluate_command_inventory },
    { "m", &Player::evaluate_command_move },
    { "move", &Player::evaluate_command_move }
  };

  const map<string, string> COMMANDS_HELP = {
    { "activate", "activate (w | a | s | d)\n  Activate something above, left, below, right respectively\n  Aliases: a" },
    { "inventory", "inventory [describe <N> | (use | give) <N> (w | a | s | d)]\n  Inspect/use items in inventory\n  Aliases: i" },
    { "move", "move (w | a | s | d)\n  Move up, left, down, right respectively\n  Aliases: g, go, m" }
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

  Inputer::validation_result_t Player::validate_command_inventory(const Inputer::command_t& command) const {
    if(command.size() == 1) {
      return { true, "" };
    }
    if(command.size() < 3) {
      return { false, "No item specified." };
    }

    int item_number;
    try {
      item_number = stoi(command[2]);
      if(item_number < 1 || item_number > inventory.size()) {
        return { false, "Invalid item number." };
      }
    } catch(invalid_argument e) {
      return { false, "Invalid distance." };
    } catch(out_of_range e) {
      return { false, "Distance too large." };
    }

    if(command[1] == "use" && command.size() > 3) {
      if(DIRECTION_COMMANDS.count(command[3]) > 0) {
        return { true, "" };
      }
      return { false, "Invalid direction." };
    }

    if(command[1] == "give") {
      if(command.size() < 4) {
        return { false, "No direction specified." };
      }
      if(DIRECTION_COMMANDS.count(command[3]) > 0) {
        return { true, "" };
      }
      return { false, "Invalid direction." };
    }
    return { true, "" };
  }

  void Player::evaluate_command_activate(Game& game, const Inputer::command_t& last_command) {
    const vector<shared_ptr<PhysicalEntity>> entities_on_target_tile = game
      .get_world()
      .get_map(position.map_id)
      .get_tile(position.step(DIRECTION_COMMANDS.at(last_command[1])))
      ->get_entities();


    const shared_ptr<PhysicalEntity> adjacent_entity = get_adjacent_entity(game, DIRECTION_COMMANDS.at(last_command[1]));
    if(adjacent_entity.get() == nullptr) {
      game.push_message("There's nothing there.");
      return;
    }
    adjacent_entity->activated_by(game, *this);
  }

  void Player::evaluate_command_inventory(Game& game, const Inputer::command_t& last_command) {
    if(last_command.size() == 1) {
      game.push_message("Inventory:");

      unsigned int n = 0;
      for(const unique_ptr<CarriedItem>& item_p : inventory) {
        stringstream ss;
        ss << "  " << ++n << ": " << item_p->get_name();
        game.push_message(ss.str());
      }
      return;
    }

    unique_ptr<CarriedItem>& targeted_item_p = inventory[stoi(last_command[2])-1];

    if(last_command[1] == "describe") {
      game.push_message(targeted_item_p->get_description());
      return;
    }

    if(last_command[1] == "use") {
      if(last_command.size() == 3) {
        targeted_item_p->activate(game, *this);
        return;
      }
      shared_ptr<PhysicalEntity> adjacent_entity = get_adjacent_entity(game, DIRECTION_COMMANDS.at(last_command[3]));
      if(adjacent_entity.get() == nullptr) {
        game.push_message("There's nothing there.");
        return;
      }
      adjacent_entity->activated_by(game, *this, *targeted_item_p);
      return;
    }

    if(last_command[1] == "give") {
      shared_ptr<PhysicalEntity> adjacent_entity = get_adjacent_entity(game, DIRECTION_COMMANDS.at(last_command[3]));
      if(adjacent_entity.get() == nullptr) {
        game.push_message("There's nothing there.");
        return;
      }
      try {
        give_item(game, std::move(targeted_item_p), dynamic_cast<Actor&>(*adjacent_entity));
      } catch(bad_cast e) {
        game.push_message("Can't give items to that.");
      }
      return;
    }
  }

  void Player::evaluate_command_move(Game& game, const Inputer::command_t& last_command) {
    if(repeat_command_times == 0 && last_command.size() > 2) {
      repeat_command_times = stoi(last_command[2]);
    }

    move(game, DIRECTION_COMMANDS.at(last_command[1]));
  }

}
