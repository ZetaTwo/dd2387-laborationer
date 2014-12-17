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
    public:
      typedef vector<string> command_t;
      command_t get_input(const Game& game);
  };
}
