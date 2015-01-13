#include "actors/goblin.h"
#include "items/questitem.h"
#include "game.h"
#include "util.h"

namespace lab3 {

  Goblin::Goblin(const WorldCoord& initial_position) : Goblin(initial_position, "Goblin") {}
  Goblin::Goblin(const WorldCoord& initial_position, const string& name) : Actor(initial_position, 10) {}

  void Goblin::do_tick(Game& game) {
    for(const direction_t dir : {DIR_NORTH, DIR_EAST, DIR_SOUTH, DIR_WEST }) {
      for(shared_ptr<Entity> entity_p : get_adjacent_entities(game, dir)) {
        if(points_to_type<Actor, shared_ptr<Entity>>(entity_p)
            && !points_to_type<Goblin, shared_ptr<Entity>>(entity_p)) {
          Actor& target = dynamic_cast<Actor&>(*entity_p);
          target.damage(game, ATTACK_DAMAGE);

          say(game, {"eeeEEEEHeeehheeEEE!!!"});
          game.push_message(easyss() << get_name() << " pokes " << target.get_name() << " with a stick!");
          return;
        }
      }
    }
    move(game, random_direction());
  }

  void Goblin::activated_by(Game& game, Actor& activator) {
    say(game, {"AAAAAHAHAHAAAAaaaaaaAAAAAA!!! *snarl*"});
  }

  void Goblin::activated_by(Game& game, Actor& activator, CarriedItem& item) {
    if(is_type<Sword, CarriedItem>(item)) {
      say(game, {"AIIEEEE!!!"});
      damage(game, 5);
    }
  }

}
