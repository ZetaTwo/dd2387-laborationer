#include <memory>

#include "player.h"
#include "actors/actor_basic.h"

using std::make_shared;

namespace lab3 {

  bool Player::possess(const shared_ptr<Actor>& new_actor) {
    actor = new_actor;
    actor->override_ticker(*this);
    return true;
  }

  void Player::do_tick(Actor& tickee) const {
  }

}
