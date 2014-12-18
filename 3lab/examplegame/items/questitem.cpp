#include "actor.h"
#include "world.h"
#include "game.h"
#include "items/questitem.h"

namespace lab3 {

  bool QuestItem::pick_up(Game& game, Actor& taker) {
    taker.add_item(QuestCarriedItem{});
    game.get_world().destroy(get_id());
    return true;
  }

}
