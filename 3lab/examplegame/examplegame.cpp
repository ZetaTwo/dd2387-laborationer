#include "examplegame.h"
#include "hazards.h"
#include "actors/human.h"

using std::make_shared;

namespace lab3 {

  void ExampleGame::initialize() {
    if (initialized) {
      throw std::runtime_error("Game has already been initialized!");
    }

    initialized = true;

    Map m;

    m.set_tile(Coord{ 3, 4 }, make_shared<FireTile>());
    m.set_tile(Coord{ 2, 1 }, make_shared<FireTile>());
    m.set_tile(Coord{ 5, 3 }, make_shared<FireTile>());

    world.add_map(std::move(m));

    shared_ptr<PhysicalEntity> player = make_shared<Player>(WorldCoord{ m.get_id(), 0, 0 });
    camera.set_followee(player);
 
    world.add_entity(player);
    world.add_entity(make_shared<Human>(WorldCoord{ m.get_id(), 0, 0 }));
    world.add_entity(make_shared<Human>(WorldCoord{ m.get_id(), 1, 1 }));
  }
}
