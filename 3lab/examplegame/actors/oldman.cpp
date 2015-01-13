#include <stdexcept>

#include "actors/oldman.h"
#include "items/questitem.h"
#include "game.h"

using std::bad_cast;

namespace lab3 {

  OldMan::OldMan(const WorldCoord& initial_position) : OldMan(initial_position, "Old man") {}

  OldMan::OldMan(const WorldCoord& initial_position, const string& name) : Human(initial_position, name) {}

  bool OldMan::is_shiny_thing(const CarriedItem& item) const {
    try {
      dynamic_cast<const CarriedShinyThing&>(item);
      return true;
    } catch(bad_cast e) {
      return false;
    }
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
          try {
            dynamic_cast<Sword&>(*item_p);

            say(game, {"Those goblins are scary! Here, take this."});
            give_item(game, std::move(item_p), activator);
            break;
          } catch(bad_cast e) {
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

}
