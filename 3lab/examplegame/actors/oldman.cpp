#include <algorithm>
#include <memory>

#include "actors/oldman.h"
#include "entities/door.h"
#include "entities/goblinquest.h"
#include "items/questitem.h"
#include "game.h"

using std::find_if;
using std::make_shared;

namespace lab3 {

  OldMan::OldMan(const WorldCoord& initial_position) : OldMan(initial_position, "Old man") {}

  OldMan::OldMan(const WorldCoord& initial_position, const string& name) : Human(initial_position, name),
    ai_state_function(AI_STATE_WAIT_FOR_SHINY_THING) {}

  bool OldMan::is_shiny_thing(const CarriedItem& item) const {
    return is_type<CarriedShinyThing, CarriedItem>(item);
  }

  bool OldMan::has_shiny_thing() const {
    for(const unique_ptr<CarriedItem>& item_p : inventory) {
      if(is_shiny_thing(*item_p)) {
        return true;
      }
    }
    return false;
  }

  void OldMan::activated_by(Game& game, Actor& activator) {
    if(has_shiny_thing()) {
        say(game, {"Thank you for finding my favourite shiny thing!"});

        for(unique_ptr<CarriedItem>& item_p : inventory) {
          if(is_type<Sword, CarriedItem>(*item_p)) {
            say(game, {"Those goblins are scary! Here, take this."});
            give_item(game, std::move(item_p), activator);
            break;
          }
        }
    } else {
        say(game, {"Have you seen my favourite shiny thing?"});
    }
  }

  void OldMan::activated_by(Game& game, Actor& activator, CarriedItem& item) {
    if(is_shiny_thing(item)) {
      say(game, {"You found my shiny thing!"});
    } else {
      say(game, {"This is not my favourite shiny thing."});
    }
  }

  void OldMan::do_tick(Game& game) {
    if(ai_state_function) {
      ai_state_function(*this, game);
    }
  }

  function<void(OldMan&, Game&)> OldMan::AI_STATE_WAIT_FOR_SHINY_THING = [](OldMan& self, Game& game) {
    if(self.has_shiny_thing()) {
      game.get_world().add_entity(make_shared<GoblinQuest>(game, self.get_position().map_id));

      self.say(game, {"AIIIIIEEE! GOBLINS!"});

      self.ai_state_function = AI_STATE_GOBLINS_PANIC;
    }
  };

  function<void(OldMan&, Game&)> OldMan::AI_STATE_GOBLINS_PANIC = [](OldMan& self, Game& game) {
    const auto adjacents = self.get_adjacent_entities(game, DIR_SOUTH);
    auto door_it = find_if(adjacents.begin(), adjacents.end(), points_to_type<Door, shared_ptr<Entity>>);

    if(door_it == adjacents.end()) {
      if(!adjacents.empty()) {
        self.say(game, "shouts", { "Get out of my way!" });
      }
      self.move(game, DIR_SOUTH);
    } else {
      if(!(*door_it)->is_solid()) {
        (*door_it)->activated_by(game, self);
      }
      self.say(game, { "Whew." });
      self.ai_state_function = AI_STATE_GO_TO_NORTH_WALL;
    }
  };

  function<void(OldMan&, Game&)> OldMan::AI_STATE_GO_TO_NORTH_WALL = [](OldMan& self, Game& game) {
    self.move(game, DIR_NORTH);
    if(! self.get_adjacent_tile(game, DIR_NORTH) -> can_enter(self)) {
      self.ai_state_function = nullptr;
    }
  };

}
