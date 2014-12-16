#include <iostream>
#include <memory>
#include <vector>

#include "actors/basic.h"
#include "game.h"
#include "map.h"
#include "tile.h"
#include "tiles/hazards.h"
#include "renderer.h"

using namespace lab3;
using std::make_shared;
using std::vector;

using std::cout;
using std::endl;

int main() {
  Game& g = *Game::get_instance();

  cout << "Map in world:" << endl;

  cout << g.get_world().get_maps().begin()->second << endl;

  g.run();
}
