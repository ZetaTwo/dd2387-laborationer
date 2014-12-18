#include "examplegame.h"
#include "actors/human.h"
#include "actors/player.h"
#include "tiles/fire.h"
#include "tiles/rock.h"

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

    for(int x = 0; x < 30; ++x) {
      m.set_tile(Coord{x, 0}, make_shared<RockTile>());
      m.set_tile(Coord{x, 15}, make_shared<RockTile>());
    }
    for(int y = 1; y < 15; ++y) {
      m.set_tile(Coord{0, y}, make_shared<RockTile>());
      m.set_tile(Coord{30, y}, make_shared<RockTile>());
    }

    world.add_map(std::move(m));

    shared_ptr<PhysicalEntity> player = make_shared<Player>(WorldCoord{ m.get_id(), 3, 4 });
    camera.set_followee(player);
 
    world.add_physical(player);
    world.add_physical(make_shared<Human>(WorldCoord{ m.get_id(), 10, 7 }));
    world.add_physical(make_shared<Human>(WorldCoord{ m.get_id(), 20, 3 }));
  }
}
