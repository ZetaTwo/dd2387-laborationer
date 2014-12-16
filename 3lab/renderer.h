#pragma once
#include <ostream>

#include "game.h"

using std::cout;

namespace lab3 {

  class Game;

  class Renderer {
      ostream& out;

    public:
      Renderer(ostream& out = cout);
      void render(const Game& game);
  };

}
