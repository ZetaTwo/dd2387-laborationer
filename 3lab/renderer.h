#pragma once
#include <ostream>

#include "game.h"

using std::cout;

namespace lab3 {

  class Game;

  class Renderer {
      ostream& out;

      ostream& render_map(ostream& os, const Game& game, const Map& map);

    public:
      Renderer(ostream& out = cout);

      void render(const Game& game);
  };

}
