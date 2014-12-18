#include "player.h"
#include "game.h"

namespace lab3 {

  void Player::input(Game& game) {
    last_command = game.get_inputer().get_input(game, *this);
  }

  Inputer::validation_result_t Player::validate_command(const Inputer::command_t& command) const {
    return Inputer::validation_result_t{false, "Not implemented"};
  }

}
