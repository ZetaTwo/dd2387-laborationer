#include "tile.h"

namespace lab3 {

  void Tile::tick(Game& game) {

    entered_entities.remove_if([](weak_ptr<Entity> entity_p) {
      return entity_p.expired();
    });

    for(const weak_ptr<Entity> entity_p : entered_entities) {
      stay(game, *(entity_p.lock()));
    }
  }

  void Tile::enter(Game& game, const weak_ptr<Entity> enterer_p) {
    entered_entities.push_back(enterer_p);
  }

  void Tile::exit(Game& game, Entity& exiter) {
    entered_entities.remove_if([&exiter](weak_ptr<Entity> entity_p) {
      return entity_p.expired() || (*(entity_p.lock()) == exiter);
    });
  }

  void Tile::stay(Game& game, Entity&) {
  }

  

}
