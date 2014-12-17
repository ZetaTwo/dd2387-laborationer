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
using std::getline;
using std::string;
using std::stringstream;

namespace lab3 {

  Inputer::command_t Inputer::get_input(const Game& game) {
    list<string> messages;


    cout << "> ";
    string line;
    getline(cin, line);

    stringstream ss(line);

    command_t command;
    string word;
    while (ss >> word) {
      command.push_back(word);
    }

    return command;
  }
}
