#include <algorithm>

#include "goblinquest.h"
#include "items/consumable.h"
#include "items/questitem.h"

using std::all_of;
using std::find_if_not;

namespace lab3 {

  GoblinQuest::GoblinQuest(Game& game, Identifiable::identifier_t map_id) :
    finished(false),
    brains_arr(new GoblinBrain[2]),
    last_known_goblin_position(WorldCoord(0, 0, 0)){

    brains_arr[0] = {
      [](Goblin& self, Game& game) -> void {
        for(const direction_t dir : {DIR_NORTH, DIR_EAST, DIR_SOUTH, DIR_WEST }) {
          for(shared_ptr<Entity> entity_p : self.get_adjacent_entities(game, dir)) {
            if(points_to_type<Actor, shared_ptr<Entity>>(entity_p)
                && !points_to_type<Goblin, shared_ptr<Entity>>(entity_p)) {
              Actor& target = dynamic_cast<Actor&>(*entity_p);
              target.damage(game, self.ATTACK_DAMAGE);

              self.say(game, {"eeeEEEEHeeehheeEEE!!!"});
              game.push_message(easyss() << self.get_name() << " pokes " << target.get_name() << " with a stick!");
              return;
            }
          }
        }
        self.move(game, random_direction());
      },
      [](Goblin& self, Game& game, Actor&) -> void {
        self.say(game, {"AAAAAHAHAHAAAAaaaaaaAAAAAA!!! *snarl*"});
      },
      [](Goblin& self, Game& game, Actor&, CarriedItem& item) -> void {
        if(is_type<Sword, CarriedItem>(item)) {
          self.say(game, {"AIIEEEE!!!"});
          self.damage(game, 5);
        }
      }
    };

    for (Coord::coord_t i = 0; i < 3; i++) {
      shared_ptr<Goblin> goblin = make_shared<Goblin>(WorldCoord{ map_id, 15, 10 + 2 * i });
      goblin->set_brain(&brains_arr[0]);
      game.get_world().add_physical(goblin);
      goblins.push_back(goblin);
    }
  }

  void GoblinQuest::tick(Game& game) {
    const auto expired = [](const weak_ptr<PhysicalEntity>& goblin_p) {
      return goblin_p.expired();
    };

    finished = all_of(goblins.begin(), goblins.end(), expired);

    if(finished) {
      game.get_world().add_physical(make_shared<Potion>(last_known_goblin_position));
      game.get_world().destroy(get_id());
    } else {
      // This will always be valid since we won't enter this block if all are expired
      last_known_goblin_position = find_if_not(goblins.begin(), goblins.end(), expired)->lock()->get_position();
    }
  }

  GoblinQuest::~GoblinQuest() {
    cout << "~GoblinQuest()" << endl;
    delete[] brains_arr;
  }

}
