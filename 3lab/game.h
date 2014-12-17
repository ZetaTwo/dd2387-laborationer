#pragma once
#include <memory>
#include <list>
#include <string>

#include "player.h"
#include "world.h"
#include "inputer.h"
#include "renderer.h"

using std::list;
using std::string;
using std::unique_ptr;

namespace lab3 {

  class Game {
      bool initialized = false;
      bool running = false;

      World world;
      Player player;
      unique_ptr<Renderer> renderer_p;
      unique_ptr<Inputer> inputer_p;

      list<string> messages;

      Game(Renderer* renderer_p, Inputer* inputer_p);

      void initialize();
      void tick();

    public:
      Game();

      void run();
      void stop();
      void render() const;

      inline const World& get_world() const { return world; }
      inline const Player& get_player() const { return player; }

      void push_message(const string& message);
      void clear_messages();
      inline const list<string>& get_messages() const { return messages; }
  };

}
