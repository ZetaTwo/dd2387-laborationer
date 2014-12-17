#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "game.h"
#include "inputer.h"

using std::cin;
using std::cout;
using std::endl;
using std::find;
using std::getline;
using std::string;
using std::stringstream;
using std::vector;

namespace lab3 {

  const vector<string> COMMANDS = {
    "g",
    "quit"
  };

  bool Inputer::validate_command(const command_t& command) const {
    return command.size() > 0 && find(COMMANDS.begin(), COMMANDS.end(), command[0]) != COMMANDS.end();
  }

  void Inputer::get_input(const Game& game) {
    list<string> messages;

    while(true) {
      game.render();

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
      while(ss >> word) {
        command.push_back(word);
      }

      if(validate_command(command)) {
        command_buffer.push_back(command);
        break;
      } else {
        stringstream ss;
        ss << "Unrecognized command: " << line;
        messages.push_back(ss.str());
      }
    }
  }

  void Inputer::evaluate_commands(Game& game) {
    for(command_t command : command_buffer) {
      if(command[0] == "quit") {
        game.stop();
      }
    }
  }

}
