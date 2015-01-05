#include "entities/door.h"
#include "game.h"

namespace lab3 {

  void Door::activated_by(Game& game, Actor&) {
    open = !open;
    if(open) {
      game.push_message("The door opens.");
    } else {
      game.push_message("The door closes.");
    }
  }

}
