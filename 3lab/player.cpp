#include <memory>

#include "player.h"
#include "actors/basic.h"

using std::make_shared;

namespace lab3 {

  Player::Player(shared_ptr<Actor> actor) : actor(actor) {}

  bool possess(Actor& new_actor) {
    return false;
  }

  void Player::do_tick(Actor& tickee) const {
  }

}
