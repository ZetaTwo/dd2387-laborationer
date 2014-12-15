#pragma once

#include "game.h"

namespace lab3 {

  class Game;

  class Renderer {
    public:
      void render(const Game& game);
  };

}
