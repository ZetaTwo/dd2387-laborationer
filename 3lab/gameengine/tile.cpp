#include <algorithm>

#include "tile.h"
#include "physicalentity.h"

namespace lab3 {

  void Tile::tick(Game& game) {

    entered_entities.remove_if([](weak_ptr<PhysicalEntity> entity_p) {
      return entity_p.expired();
    });

    for (const weak_ptr<PhysicalEntity> entity_p : entered_entities) {
      stay(game, *(entity_p.lock()));
    }
  }

  void Tile::enter(Game& game, const weak_ptr<PhysicalEntity> enterer_p) {
    entered_entities.push_back(enterer_p);

    //Call enter hook
    this->do_enter(game, enterer_p);
  }

  void Tile::exit(Game& game, PhysicalEntity& exiter) {
    entered_entities.remove_if([&exiter](weak_ptr<PhysicalEntity> entity_p) {
      return entity_p.expired() || (*(entity_p.lock()) == exiter);
    });

    //Call exit hook
    this->do_exit(game, exiter);
  }

  void Tile::stay(Game& game, PhysicalEntity& stayer) {
    //Call stay hook
    this->do_stay(game, stayer);
  }

  list<shared_ptr<PhysicalEntity>> Tile::get_entities() const {
    list<shared_ptr<PhysicalEntity>> result;
    for (const weak_ptr<PhysicalEntity> p : entered_entities) {
      if (!p.expired()) {
        result.push_back(p.lock());
      }
    }

    sort(result.begin(), result.end(), PhysicalEntityRenderOrderSorter());

    return result;
  }

  shared_ptr<PhysicalEntity> Tile::get_entity() const {
    for (const weak_ptr<PhysicalEntity> p : entered_entities) {
      if (!p.expired()) {
        shared_ptr<PhysicalEntity> res = p.lock();
        if (res->is_visible()) {
          return res;
        }
      }
    }

    return nullptr;
  }
}
