#include <sstream>

#include "game.h"
#include "hazards.h"

using std::ostringstream;

namespace lab3 {

  FireTile::FireTile() : damage(1) {}

  string FireTile::description = "Fire!";

  void FireTile::enter(weak_ptr<Entity> enterer_p) {
    Tile::enter(enterer_p);
    if(!enterer_p.expired()) {
      ostringstream ss;
      ss << enterer_p.lock()->get_name() << " is on fire!";
      Game::get_instance()->push_message(ss.str());
    }
  }

  void FireTile::exit(Entity& exiter) {
    Tile::exit(exiter);
    ostringstream ss;
    ss << exiter.get_name() << " isn't on fire anymore!";
    Game::get_instance()->push_message(ss.str());
  }

  void FireTile::stay(Entity& stayer) {
    Tile::stay(stayer);
    ostringstream ss;
    ss << stayer.get_name() << " is still on fire!";
    Game::get_instance()->push_message(ss.str());
  }

}
