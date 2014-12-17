#pragma once
#include <memory>
#include <list>
#include <string>

#include "inputer.h"
#include "player.h"
#include "renderer.h"
#include "world.h"

using std::list;
using std::string;
using std::shared_ptr;

namespace lab3 {

  class Renderer;

  class Game {
      bool initialized = false;
      bool running = false;

      World world;
      Player player;
      shared_ptr<Renderer> renderer_p;
      shared_ptr<Inputer> inputer_p;

      list<string> messages;

      
      Game(shared_ptr<Renderer> renderer_p, shared_ptr<Inputer> inputer_p);

      void initialize();
      void tick();

    public:
      Game();

      void run();
      void stop();

      inline const World& get_world() const { return world; }
      inline const Player& get_player() const { return player; }

      void push_message(const string& message);
      void clear_messages();
      inline const list<string>& get_messages() const { return messages; }
  };

}
