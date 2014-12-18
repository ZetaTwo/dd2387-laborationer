#include <stdexcept>

#include "actors/oldman.h"
#include "items/questitem.h"
#include "game.h"

using std::bad_cast;

namespace lab3 {

  OldMan::OldMan(const WorldCoord& initial_position) : OldMan(initial_position, "Old man") {}

  OldMan::OldMan(const WorldCoord& initial_position, const string& name) : Human(initial_position, name) {}

  void OldMan::activated_by(Game& game, Actor& activator) {
    stringstream ss;

    ss << get_name() << " says:" << endl;

    switch(inventory.size()) {
      case 0:
        ss << "Have you seen my favourite shiny thing?" << endl;
        break;
      case 1:
        ss << "Thank you for finding my favourite shiny thing!" << endl;
        break;
    }

    game.push_message(ss.str());
  }

  void OldMan::activated_by(Game& game, Actor& activator, CarriedItem& item) {
    stringstream ss;
    ss << get_name() << " says:" << endl;
    try {
      dynamic_cast<CarriedShinyThing&>(item);

      ss << "You found my shiny thing!" << endl;
    } catch(bad_cast e) {
      ss << "This is not my favourite shiny thing." << endl;
    }
    game.push_message(ss.str());
  }

}
