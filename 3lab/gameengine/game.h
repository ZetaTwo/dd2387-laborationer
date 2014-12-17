#pragma once
#include <memory>
#include <list>
#include <string>

#include "camera.h"
#include "world.h"
#include "inputer.h"
#include "renderer.h"

using std::list;
using std::string;
using std::unique_ptr;

namespace lab3 {

  class Game {
  protected:
      bool initialized = false;
      bool running = false;

      World world;
      Camera camera;
      unique_ptr<Renderer> renderer_p;
      unique_ptr<Inputer> inputer_p;

      list<string> messages;

      Game(Renderer* renderer_p, Inputer* inputer_p);

      virtual void initialize() = 0;
      void tick();

    public:
      Game();

      void run();
      void stop();
      Inputer::command_t get_input() const;
      void render() const;

      inline const World& get_world() const { return world; }
      inline const Camera& get_camera() const { return camera; }

      void push_message(const string& message);
      void clear_messages();
      inline const list<string>& get_messages() const { return messages; }

      inline Inputer& get_inputer() const { return *inputer_p; }
  };

}
