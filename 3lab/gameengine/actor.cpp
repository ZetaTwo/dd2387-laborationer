#include <algorithm>
#include <utility>

#include "actor.h"
#include "game.h"

using std::endl;
using std::find;
using std::find_if;
using std::weak_ptr;

namespace lab3 {

  bool Actor::move(Game& game, direction_t direction, unsigned int distance) {
    return game.get_world().move_entity(game, *this, position.step(direction, distance));
  }

  void Actor::emote(Game& game, initializer_list<string> utterance) const {
    EasyStringStream ss;
    ss << get_name() << " ";

    for(const string s : utterance) {
      ss << s;
    }

    game.push_message(ss);
  }

  void Actor::say(Game& game, string say_type, initializer_list<string> utterance) const {
    EasyStringStream ss;
    ss << get_name() << " " << say_type << ": ";

    for(const string s : utterance) {
      ss << s;
    }

    game.push_message(ss);
  }

  bool Actor::add_item(Game& game, unique_ptr<CarriedItem>&& item_p) {
    inventory.emplace_back(std::move(item_p));

    game.push_message(easyss() << get_name() << " picked up " << inventory.back()->get_name());

    return true;
  }

  bool Actor::drop_item(CarriedItem& item) {
    return false;
  }

  bool Actor::give_item(Game& game, unique_ptr<CarriedItem>&& item_p, Actor& recipient) {
    const CarriedItem& item = *item_p;
    inventory_t::iterator erase_it = find(inventory.begin(), inventory.end(), item_p);
    if(erase_it != inventory.end()) {
      recipient.add_item(game, std::move(item_p));
      inventory.erase(erase_it);

      game.push_message(easyss() << get_name() << " gave " << item.get_name() << " to " << recipient.get_name());

      return true;
    }
    return false;
  }

  bool Actor::remove_item(CarriedItem& item) {
    const inventory_t::iterator found_it = find_if(inventory.begin(), inventory.end(),
      [&item](const unique_ptr<CarriedItem>& item_p) {
        return item_p->get_id() == item.get_id();
      }
    );
    if(found_it != inventory.end()) {
      inventory.erase(found_it);
      return true;
    }
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

  void Actor::damage(Game& game, const int damage) {
    health -= damage;
    game.push_message(easyss() << get_name() << " takes " << damage << " damage (" << health << " hp)!");

    if(health <= 0) {
      game.get_world().destroy(get_id());

      game.push_message(easyss() << get_name() << " dies from damage!");
    }
  }
}
