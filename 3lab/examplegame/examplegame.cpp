#include "examplegame.h"
#include "actors/oldman.h"
#include "actors/evilking.h"
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

    start_message();

    Identifiable::identifier_t map_id = create_map();

    shared_ptr<PhysicalEntity> player = make_shared<Player>(WorldCoord{ map_id, 3, 10 });
    camera.set_followee(player);
 
    world.add_physical(player);
    world.add_physical(make_shared<OldMan>(WorldCoord{ map_id, 5, 4 }));
    world.add_physical(make_shared<EvilKing>(WorldCoord{ map_id, 28, 10 }));
  }

  void ExampleGame::start_message() const {
    cout << "Welcome!" << endl;
    cout << "There is an evil king ruling over the kingdom. " << endl;
    cout << "Yada yada yada. <Generic fantasy RPG background here>." << endl;
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
      else {
        //m.set_tile(Coord{ 20, y }, make_shared<MagicDoorTile>());
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
    world.add_map(std::move(m));

    return id;
  }
}
