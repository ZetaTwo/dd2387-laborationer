#include "actors/oldman.h"
#include "game.h"

namespace lab3 {

  OldMan::OldMan(const WorldCoord& initial_position) : OldMan(initial_position, "Old man") {}

  OldMan::OldMan(const WorldCoord& initial_position, const string& name) : Human(initial_position, name) {}

  void OldMan::activated_by(Entity& activator) {
  }


}
