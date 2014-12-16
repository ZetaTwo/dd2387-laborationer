#include<memory>

#include "actors/basic.h"
#include "game.h"

using std::make_shared;

namespace lab3 {

  Game::Game() :
    player(Player{make_shared<Human>(WorldCoord{world.get_maps().begin()->first, 0, 0}, "Ze Hero")}),
    inputer_p(make_shared<Inputer>()) { }

  void Game::run() {
    world.tick();
    world.tick();
    world.tick();
    world.tick();
  }

}
