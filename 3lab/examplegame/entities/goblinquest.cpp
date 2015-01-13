#include <algorithm>

#include "goblinquest.h"

using std::all_of;

namespace lab3 {

  GoblinQuest::GoblinQuest(Game& game, Identifiable::identifier_t map_id) : finished(false) {
    for (Coord::coord_t i = 0; i < 3; i++) {
      shared_ptr<PhysicalEntity> goblin = make_shared<Goblin>(WorldCoord{ map_id, 15, 10 + 2 * i });
      game.get_world().add_physical(goblin);
      goblins.push_back(goblin);
    }
  }

  void GoblinQuest::tick(Game& game) {
    finished = all_of(goblins.begin(), goblins.end(), [](const weak_ptr<PhysicalEntity>& goblin_p) {
      return goblin_p.expired();
    });
  }

}
