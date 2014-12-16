#include "actor.h"

using std::set;
using std::weak_ptr;

namespace lab3 {

  bool Actor::move(direction_t direction, unsigned int distance) {
    return false;
  }

  bool Actor::add_item(CarriedItem& item) {
    return false;
  }

  bool Actor::drop_item(CarriedItem& item) {
    return false;
  }

  bool Actor::give_item(CarriedItem& item, Actor& recipient) {
    return false;
  }

  bool Actor::remove_item(CarriedItem& item) {
    return false;
  }

  bool Actor::override_ticker(ActorTicker& ticker_override) {
    return false;
  }

  void Actor::interact(Actor& interactee) {}

  void Actor::tick() {
    if(!ticker_override_p.expired()) {
      ticker_override_p.lock()->do_tick(*this);
    }
    do_tick(*this);
  }

}
