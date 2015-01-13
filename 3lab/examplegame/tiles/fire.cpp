#include "game.h"
#include "tiles/fire.h"

namespace lab3 {

  FireTile::FireTile() : damage(1) {}

  const string FireTile::description = "Fire!";

  void FireTile::do_enter(Game& game, weak_ptr<PhysicalEntity> enterer_p) {
    if(!enterer_p.expired()) {
      game.push_message(easyss() << enterer_p.lock()->get_name() << " is on fire!");
    }
  }

  void FireTile::do_exit(Game& game, PhysicalEntity& exiter) {
    game.push_message(easyss() << exiter.get_name() << " isn't on fire anymore!");
  }

  void FireTile::do_stay(Game& game, PhysicalEntity& stayer) {
    game.push_message(easyss() << stayer.get_name() << " is still on fire!");
  }

}
