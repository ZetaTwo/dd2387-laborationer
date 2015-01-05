#pragma once
#include <list>
#include <string>

#include "camera.h"
#include "renderer.h"
#include "inputer.h"
#include "world.h"

using std::list;
using std::string;

namespace lab3 {

  class Game {
  protected:
      bool initialized = false;
      bool running = false;

      World world;
      Camera camera;
      Renderer* renderer_p;
      Inputer* inputer_p;

      list<string> messages;

      Game(Renderer* renderer_p, Inputer* inputer_p);
      ~Game();

      virtual void initialize() = 0;
      void tick();

    public:
      Game();

      void run();
      void stop();
      void render() const;

      inline const World& get_world() const { return world; }
      inline World& get_world() { return world; }
      inline const Camera& get_camera() const { return camera; }

      void push_message(const string& message);
      void clear_messages();
      inline const list<string>& get_messages() const { return messages; }

      inline Inputer& get_inputer() const { return *inputer_p; }
  };

}
