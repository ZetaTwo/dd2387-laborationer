#pragma once
#include <ostream>

#include "game.h"

namespace lab3 {

  class Game;
  class Map;

  class Renderer {
    std::ostream& out;
    std::ostream& render_map(std::ostream& os, const Game& game, const Map& map);

  public:
    Renderer(std::ostream& out = std::cout);
    void render(const Game& game);
  };
}
