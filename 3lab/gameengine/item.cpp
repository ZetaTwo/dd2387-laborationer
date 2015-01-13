#include "game.h"
#include "item.h"

namespace lab3 {

  void CarriedItem::activate(Game& game, Actor&) {
    game.push_message("Nothing happens.");
  }

}
