#pragma once
#include <memory>

#include "inputer.h"
#include "player.h"
#include "renderer.h"
#include "world.h"

namespace lab3 {

  class Renderer;

  class Game {
      World world;
      Player player;
      shared_ptr<Renderer> renderer_p;
      shared_ptr<Inputer> inputer_p;

      Game();
      Game(shared_ptr<Renderer> renderer_p, shared_ptr<Inputer> inputer_p);

      void tick();

    public:
      void run();

      inline const World& get_world() const { return world; }
      inline const Player& get_player() const { return player; }

    private:
      static shared_ptr<Game> the_instance;

    public:
      static shared_ptr<Game> get_instance() {
        if(the_instance.get() == nullptr) {
          the_instance.reset(new Game());
        }
        return the_instance;
      }
  };

}
