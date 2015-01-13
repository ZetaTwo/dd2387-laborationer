#include "deathquest.h"
#include "util.h"

namespace lab3 {

  void DeathQuest::tick(Game& game) {
    if(hero_p.expired() || hero_p.lock()->get_health() <= 0) {
      game.push_message(easyss() << "You are dead.\n"
          << "The evil ruler will forever rule evilly over the kingdom.\n"
          << "There is no hope for the people.\n"
          << "Game over.");
      game.stop();
    }
  }

}
