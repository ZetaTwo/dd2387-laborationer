#include <sstream>

#include "game.h"
#include "hazards.h"

using std::ostringstream;

namespace lab3 {

  FireTile::FireTile() : damage(1) {}

  string FireTile::description = "Fire!";

  void FireTile::enter(Game& game, weak_ptr<Entity> enterer_p) {
    Tile::enter(game, enterer_p);
    if(!enterer_p.expired()) {
      ostringstream ss;
      ss << enterer_p.lock()->get_name() << " is on fire!";
      game.push_message(ss.str());
    }
  }

  void FireTile::exit(Game& game, Entity& exiter) {
    Tile::exit(game, exiter);
    ostringstream ss;
    ss << exiter.get_name() << " isn't on fire anymore!";
    game.push_message(ss.str());
  }

  void FireTile::stay(Game& game, Entity& stayer) {
    Tile::stay(game, stayer);
    ostringstream ss;
    ss << stayer.get_name() << " is still on fire!";
    game.push_message(ss.str());
  }

}
