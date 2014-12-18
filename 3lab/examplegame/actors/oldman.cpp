#include <stdexcept>

#include "actors/oldman.h"
#include "items/questitem.h"
#include "game.h"

using std::bad_cast;

namespace lab3 {

  OldMan::OldMan(const WorldCoord& initial_position) : OldMan(initial_position, "Old man") {}

  OldMan::OldMan(const WorldCoord& initial_position, const string& name) : Human(initial_position, name) {}

  bool OldMan::is_shiny_thing(const CarriedItem& item) const {
    try {
      dynamic_cast<const CarriedShinyThing&>(item);
      return true;
    } catch(bad_cast e) {
      return false;
    }
  }

  bool OldMan::has_shiny_thing() const {
    for(const unique_ptr<CarriedItem>& item_p : inventory) {
      if(is_shiny_thing(*item_p)) {
        return true;
      }
    }
    return false;
  }

  void OldMan::activated_by(Game& game, Actor& activator) {
    stringstream ss;
    ss << get_name() << " says:" << endl;

    if(has_shiny_thing()) {
        ss << "Thank you for finding my favourite shiny thing!" << endl;

        for(unique_ptr<CarriedItem>& item_p : inventory) {
          try {
            dynamic_cast<Sword&>(*item_p);

            ss << "Here, take this." << endl;
            give_item(game, std::move(item_p), activator);
            break;
          } catch(bad_cast e) {
          }
        }
    } else {
        ss << "Have you seen my favourite shiny thing?" << endl;
    }

    game.push_message(ss.str());
  }

  void OldMan::activated_by(Game& game, Actor& activator, CarriedItem& item) {
    stringstream ss;
    ss << get_name() << " says:" << endl;

    if(is_shiny_thing(item)) {
      ss << "You found my shiny thing!" << endl;
    } else {
      ss << "This is not my favourite shiny thing." << endl;
    }
    game.push_message(ss.str());
  }

}
