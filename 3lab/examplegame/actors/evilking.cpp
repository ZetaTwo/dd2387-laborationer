#include <sstream>

#include "actors/evilking.h"
#include "game.h"
#include "item.h"
#include "items/questitem.h"

using std::stringstream;

namespace lab3 {

  EvilKing::EvilKing(const WorldCoord& initial_position) : EvilKing(initial_position, "Evil King") {}

  EvilKing::EvilKing(const WorldCoord& initial_position, const string& name) : Human(initial_position, name), hitpoints(3) {}

  void EvilKing::do_tick(Game& game) {
  }

  void EvilKing::activated_by(Game& game, Actor& activator) {
    say(game, {"Hohoho! Right thplendid day today, ith it not, o loyal minion?"});
  }

  void EvilKing::activated_by(Game& game, Actor& activator, CarriedItem& item) {
    stringstream ss;
    if(is_type<Sword, CarriedItem>(item)) {
      if(hitpoints == 3) {
        say(game, {"O rly?"});
      }
      say(game, {"IMMA CHARGIN' MAH LEEYZAAAH!!!"});

      if(--hitpoints < 1) {
        say(game, {"*gurgel*"});
      }

      if(hitpoints < 1) {
        emote(game, {"collapses."});

        game.get_world().destroy(get_id());
      }
    } else {
      say(game, {"Hohoho! What haveth thou there, o loyal minion?"});
    }

  }

}
