#include <sstream>
#include <stdexcept>

#include "actors/evilking.h"
#include "game.h"
#include "item.h"
#include "items/questitem.h"

using std::bad_cast;
using std::stringstream;

namespace lab3 {

  EvilKing::EvilKing(const WorldCoord& initial_position) : EvilKing(initial_position, "Evil King") {}

  EvilKing::EvilKing(const WorldCoord& initial_position, const string& name) : Human(initial_position, name), hitpoints(3) {}

  void EvilKing::do_tick(Game& game) {
  }

  void EvilKing::activated_by(Game& game, Actor& activator) {
    stringstream ss;
    ss << get_name() << " says:" << endl;
    ss << "Hohoho! Right thplendid day today, ith it not, o loyal minion?" << endl;
    game.push_message(ss.str());
  }

  void EvilKing::activated_by(Game& game, Actor& activator, CarriedItem& item) {
    stringstream ss;
    try {
      dynamic_cast<Sword&>(item);

      if(hitpoints == 3) {
        ss << "O rly?" << endl;
      }
      ss << "IMMA CHARGIN' MAH LEEYZAAAH!!!" << endl;

      if(--hitpoints < 1) {
        ss << "*gurgel*" << endl;
      }
      game.push_message(ss.str());

      if(hitpoints < 1) {
        stringstream collapse_ss;
        collapse_ss.clear();
        collapse_ss << get_name() << " collapses.";
        game.push_message(collapse_ss.str());

        game.get_world().destroy(get_id());
      }
    } catch(bad_cast e) {
      ss << "Hohoho! What haveth thou there, o loyal minion?" << endl;
      game.push_message(ss.str());
    }

  }

}
