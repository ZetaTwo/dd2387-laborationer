#include "kingquest.h"

#include "actors/evilking.h"

namespace lab3 {

  KingQuest::KingQuest(Game& game, Identifiable::identifier_t map_id) {
    shared_ptr<PhysicalEntity> k = make_shared<EvilKing>(WorldCoord{ map_id, 28, 10 });
    game.get_world().add_physical(k);
    king = k;
  }

  void KingQuest::tick(Game& game) {
    if (king.expired()) {

      cout << "You won! Hurray!" << endl;

      game.stop();
    }
  }

}