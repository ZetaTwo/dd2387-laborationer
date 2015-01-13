#include <memory>

#include "actor.h"
#include "world.h"
#include "game.h"
#include "items/questitem.h"

using std::unique_ptr;

namespace lab3 {

  bool ShinyThing::pick_up(Game& game, Actor& taker) {
    taker.add_item(game, unique_ptr<CarriedShinyThing>{new CarriedShinyThing{}});
    game.get_world().destroy(get_id());
    return true;
  }

  bool DullThing::pick_up(Game& game, Actor& taker) {
    taker.add_item(game, unique_ptr<CarriedDullThing>{new CarriedDullThing{}});
    game.get_world().destroy(get_id());
    return true;
  }

}
