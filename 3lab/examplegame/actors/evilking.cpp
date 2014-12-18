#include "actors/evilking.h"
#include "game.h"

namespace lab3 {

  EvilKing::EvilKing(const WorldCoord& initial_position) : EvilKing(initial_position, "Evil King") {}

  EvilKing::EvilKing(const WorldCoord& initial_position, const string& name) : Human(initial_position, name) {}

  void EvilKing::do_tick(Game& game) {
  }

  void EvilKing::activated_by(Game& game, Actor& activator) {
  }

}
