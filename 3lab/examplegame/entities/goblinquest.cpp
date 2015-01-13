#include "goblinquest.h"

namespace lab3 {

  GoblinQuest::GoblinQuest(Game& game, Identifiable::identifier_t map_id) : finished(false) {
    for (Coord::coord_t i = 0; i < 3; i++) {
      shared_ptr<PhysicalEntity> goblin = make_shared<Goblin>(WorldCoord{ map_id, 15, 12 + 2 * i });
      game.get_world().add_physical(goblin);
      goblins.push_back(goblin);
    }
  }

  void GoblinQuest::tick(Game& game) {
    bool alldead = true;
    for (const auto& p : goblins) {
      if (!p.expired()) {
        alldead = false;
      }
    }
    finished = alldead;
  }

}