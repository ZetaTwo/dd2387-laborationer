#include "actors/oldman.h"
#include "game.h"

namespace lab3 {

  OldMan::OldMan(const WorldCoord& initial_position) : Actor(initial_position) {}

  OldMan::OldMan(const WorldCoord& initial_position, const string& name) : Actor(initial_position) {}

  void OldMan::do_tick(Game& game) {
  }

  void OldMan::activated_by(Entity& activator) {
  }


}
