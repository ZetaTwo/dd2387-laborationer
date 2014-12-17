#include <memory>

#include "player.h"
#include "actor.h"

using std::make_shared;

namespace lab3 {

  bool Player::possess(const shared_ptr<Actor>& new_actor) {
    if(actor.get() != nullptr) {
      actor->set_remote_controlled(false);
    }
    actor = new_actor;
    actor->set_remote_controlled(true);
    return true;
  }

  void Player::do_tick(Actor& tickee) const {
  }

}
