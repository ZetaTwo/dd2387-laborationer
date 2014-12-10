#pragma once
#include <memory>

#include "inputer.h"
#include "player.h"
#include "renderer.h"
#include "world.h"

namespace lab3 {

  class Game {
      World world;
      Player player;
      Renderer renderer;
      shared_ptr<Inputer> inputer_p;

    public:
      void run();
  };

}
