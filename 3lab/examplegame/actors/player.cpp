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

    if(command[0] == "g") {
      if(command.size() > 1) {
        if(DIRECTION_COMMANDS.count(command[1]) > 0) {
          return { true, "" };
        }
        return { false, "Invalid direction." };
      }
      return { false, "No direction specified." };
    }

    return { false, "Unrecognized command." };
  }

}
