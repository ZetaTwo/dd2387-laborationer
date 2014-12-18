#include <stdexcept>
#include <utility>

#include "examplegame.h"
#include "actors/oldman.h"
#include "actors/player.h"
#include "entities/kingquest.h"
#include "tiles/rock.h"
#include "entities/door.h"

using std::make_shared;
using std::move;
using std::runtime_error;

namespace lab3 {

  void ExampleGame::initialize() {
    if (initialized) {
      throw runtime_error("Game has already been initialized!");
    }
    initialized = true;

    start_message();

    Identifiable::identifier_t map_id = create_map();

    shared_ptr<PhysicalEntity> player = make_shared<Player>(WorldCoord{ map_id, 3, 10 });
    camera.set_followee(player);
 
    world.add_physical(player);
    world.add_physical(make_shared<OldMan>(WorldCoord{ map_id, 5, 4 }));
    world.add_physical(make_shared<Door>(WorldCoord{ map_id, 20, 8 }));
    world.add_entity(make_shared<KingQuest>(*this, map_id));
  }

  void ExampleGame::start_message() const {
    cout << "Welcome!" << endl;
    cout << "There is an evil ruler ruling evilly over the kingdom. " << endl;
    cout << "Yada yada yada, you know what to do." << endl;
    cout << endl;
    cout << "View available commands with \"help\"." << endl;
    cout << "Press enter to start." << endl;
    cin.get();
  }

  Identifiable::identifier_t ExampleGame::create_map() {
    Map m;

    //Walls
    for (Coord::coord_t x = 0; x <= 30; ++x) {
      m.set_tile(Coord{ x, 0 }, make_shared<RockTile>());
      m.set_tile(Coord{ x, 15 }, make_shared<RockTile>());
    }
    for (Coord::coord_t y = 1; y < 15; ++y) {
      m.set_tile(Coord{ 0, y }, make_shared<RockTile>());
      m.set_tile(Coord{ 30, y }, make_shared<RockTile>());

      if (y != 8) {
        m.set_tile(Coord{ 20, y }, make_shared<RockTile>());
      }
    }

    //House
    m.set_tile(Coord{ 3, 3 }, make_shared<RockTile>());
    m.set_tile(Coord{ 4, 3 }, make_shared<RockTile>());
    m.set_tile(Coord{ 5, 3 }, make_shared<RockTile>());
    m.set_tile(Coord{ 6, 3 }, make_shared<RockTile>());
    m.set_tile(Coord{ 7, 3 }, make_shared<RockTile>());
    m.set_tile(Coord{ 3, 6 }, make_shared<RockTile>());
    m.set_tile(Coord{ 4, 6 }, make_shared<RockTile>());
    m.set_tile(Coord{ 6, 6 }, make_shared<RockTile>());
    m.set_tile(Coord{ 7, 6 }, make_shared<RockTile>());
    m.set_tile(Coord{ 3, 4 }, make_shared<RockTile>());
    m.set_tile(Coord{ 3, 5 }, make_shared<RockTile>());
    m.set_tile(Coord{ 7, 4 }, make_shared<RockTile>());
    m.set_tile(Coord{ 7, 5 }, make_shared<RockTile>());

    Identifiable::identifier_t id = m.get_id();
    world.add_map(move(m));

    return id;
  }
}
