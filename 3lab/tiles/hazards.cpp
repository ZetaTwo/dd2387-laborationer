#include "hazards.h"

#include<iostream>
using std::cout;
using std::endl;

namespace lab3 {

  FireTile::FireTile() : damage(1) {}

  string FireTile::description = "Fire!";

  void FireTile::enter(weak_ptr<Entity> enterer_p) {
    Tile::enter(enterer_p);
    if(!enterer_p.expired()) {
      cout << enterer_p.lock()->get_name() << " is on fire!" << endl;
    }
  }

  void FireTile::exit(Entity& exiter) {
    Tile::exit(exiter);
    cout << exiter.get_name() << " isn't on fire anymore!" << endl;
  }

  void FireTile::stay(Entity& stayer) {
    Tile::stay(stayer);
    cout << stayer.get_name() << " is still on fire!" << endl;
  }

}
