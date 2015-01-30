#include <memory>

#include "actor.h"
#include "world.h"
#include "game.h"
#include "items/consumable.h"

using std::unique_ptr;

namespace lab3 {

  bool Potion::pick_up(Game& game, Actor& taker) {
    taker.add_item(game, unique_ptr<CarriedPotion>{new CarriedPotion{}});
    game.get_world().destroy(get_id());
    return true;
  }

}
