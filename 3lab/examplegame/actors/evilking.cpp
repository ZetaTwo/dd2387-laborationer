#include "actors/evilking.h"
#include "game.h"

namespace lab3 {

  EvilKing::EvilKing(const WorldCoord& initial_position) : Actor(initial_position) {}

  EvilKing::EvilKing(const WorldCoord& initial_position, const string& name) : Actor(initial_position) {}

  void EvilKing::do_tick(Game& game) {
  }

  void EvilKing::activated_by(Entity& activator) {
  }

}
