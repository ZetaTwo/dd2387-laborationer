#include "player.h"
#include "game.h"

namespace lab3 {
  void Player::input(Game& input) {
    last_command = input.get_input();
  }
}