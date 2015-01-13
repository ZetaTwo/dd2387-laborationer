#include "actors/goblin.h"
#include "game.h"

namespace lab3 {

  Goblin::Goblin(const WorldCoord& initial_position) : Actor(initial_position) {}

  Goblin::Goblin(const WorldCoord& initial_position, const string& name) : Actor(initial_position) {}

  void Goblin::do_tick(Game& game) {
  }

  void Goblin::activated_by(Game& game, Actor& activator) {
  }

  void Goblin::activated_by(Game& game, Actor& activator, CarriedItem& item) {
  }

}