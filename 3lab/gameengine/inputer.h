#pragma once
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "inputer.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::list;
using std::pair;
using std::string;
using std::stringstream;
using std::vector;

namespace lab3 {

  class Game;

  class Inputer {
    public:
      typedef vector<string> command_t;
      typedef pair<bool, string> validation_result_t;

      void render_game(const Game& game) const;

      template<class T>
      command_t get_input(const Game& game, const T& command_validator);

  };

  template<class T>
  Inputer::command_t Inputer::get_input(const Game& game, const T& command_validator) {
    list<string> messages;

    while(true) {
      for(string message : messages) {
        cout << message << endl;
      }
      messages.clear();

      cout << "> ";
      string line;
      getline(cin, line);

      stringstream ss(line);

      command_t command;
      string word;
      while (ss >> word) {
        command.push_back(word);
      }

      const validation_result_t validation_result = command_validator.validate_command(command);
      if(validation_result.first) {
        return command;
      }
      messages.push_back(validation_result.second);

      render_game(game);
    }
  }
}
