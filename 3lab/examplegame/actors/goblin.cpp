#include "actors/goblin.h"
#include "game.h"
#include "util.h"

namespace lab3 {

  Goblin::Goblin(const WorldCoord& initial_position) : Goblin(initial_position, "Goblin") {}
  Goblin::Goblin(const WorldCoord& initial_position, const string& name) : Actor(initial_position, 10) {}

  void Goblin::set_brain(GoblinBrain* brain_p) {
    this->brain_p = brain_p;
  }

  void Goblin::do_tick(Game& game) {
    if(brain_p == nullptr) {
      say(game, {"Hurr durr..."});
    } else {
      brain_p->do_tick(*this, game);
    }
  }

  void Goblin::activated_by(Game& game, Actor& activator) {
    if(brain_p == nullptr) {
      say(game, {"Bleh?"});
    } else {
      brain_p->activated_by(*this, game, activator);
    }
  }

  void Goblin::activated_by(Game& game, Actor& activator, CarriedItem& item) {
    if(brain_p == nullptr) {
      say(game, {"Bleh, hurr durr..."});
    } else {
      brain_p->activated_with_item(*this, game, activator, item);
    }
  }

}
