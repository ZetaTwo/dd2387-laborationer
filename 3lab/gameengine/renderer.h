#pragma once
#include <iostream>

using std::cout;
using std::ostream;

namespace lab3 {

  class Game;
  class Map;

  class Renderer {
    ostream& out;
    ostream& render_map(ostream& os, const Game& game, const Map& map);

  public:
    Renderer(ostream& out = cout);
    void render(const Game& game);
  };
}
