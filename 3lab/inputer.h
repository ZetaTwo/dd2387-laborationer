#pragma once
#include <list>
#include <string>
#include <vector>

using std::list;
using std::string;
using std::vector;

namespace lab3 {

  class Game;

  class Inputer {
      typedef vector<string> command_t;

      list<command_t> command_buffer;

      bool validate_command(const command_t& command) const;

    public:
      void get_input(Game& game);
      void evaluate_commands(Game& game);
  };
}
