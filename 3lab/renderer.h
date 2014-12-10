#pragma once

#include "game.h"

namespace lab3 {

  class Game;

  class Renderer {
    public:
      Renderer& render(const Game& game);
  };

}
