#include <sstream>

#include "game.h"
#include "tiles/fire.h"

using std::ostringstream;

namespace lab3 {

  FireTile::FireTile() : damage(1) {}

  const string FireTile::description = "Fire!";

  void FireTile::do_enter(Game& game, weak_ptr<PhysicalEntity> enterer_p) {
    if(!enterer_p.expired()) {
      ostringstream ss;
      ss << enterer_p.lock()->get_name() << " is on fire!";
      game.push_message(ss.str());
    }
  }

  void FireTile::do_exit(Game& game, PhysicalEntity& exiter) {
    ostringstream ss;
    ss << exiter.get_name() << " isn't on fire anymore!";
    game.push_message(ss.str());
  }

  void FireTile::do_stay(Game& game, PhysicalEntity& stayer) {
    ostringstream ss;
    ss << stayer.get_name() << " is still on fire!";
    game.push_message(ss.str());
  }

}
