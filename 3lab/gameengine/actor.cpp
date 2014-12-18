#include <utility>

#include "actor.h"
#include "game.h"

using std::set;
using std::weak_ptr;

namespace lab3 {

  bool Actor::move(Game& game, direction_t direction, unsigned int distance) {
    return game.get_world().move_entity(game, *this, position.step(direction, distance));
  }

  bool Actor::add_item(Game& game, unique_ptr<CarriedItem>&& item_p) {
    pair<set<unique_ptr<CarriedItem>>::const_iterator, bool> inserted = inventory.emplace(std::move(item_p));

    if(inserted.second) {
      stringstream ss;
      ss << "Picked up " << (*inserted.first)->get_name();
      game.push_message(ss.str());
    }
    return inserted.second;
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

  bool Actor::set_remote_controlled(bool is_remote_controlled) {
    this->is_remote_controlled = is_remote_controlled;
    return true;
  }

  void Actor::interact(Actor& interactee) {}

  void Actor::tick(Game& game) {
    if(!is_remote_controlled) {
      do_tick(game);
    }
  }

  void Actor::do_tick(Game& game) {
  }

}
