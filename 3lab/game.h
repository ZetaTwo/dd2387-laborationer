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
      Game();

      void run();

      inline const World& get_world() const { return world; }
      inline const Player& get_player() const { return player; }
  };

}
