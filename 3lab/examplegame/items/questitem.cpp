#include <memory>

#include "actor.h"
#include "world.h"
#include "game.h"
#include "items/questitem.h"

using std::unique_ptr;

namespace lab3 {

  bool QuestItem::pick_up(Game& game, Actor& taker) {
    taker.add_item(game, unique_ptr<QuestCarriedItem>{new QuestCarriedItem{}});
    game.get_world().destroy(get_id());
    return true;
  }

}
