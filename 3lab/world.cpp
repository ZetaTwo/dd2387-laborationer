#include<memory>

#include "actors/basic.h"
#include "tiles/hazards.h"
#include "world.h"

using std::make_shared;
using std::pair;

namespace lab3 {

  World::World() {
    Map m;

    m.set_tile(Coord{3, 4}, std::make_shared<FireTile>());
    m.set_tile(Coord{2, 1}, std::make_shared<FireTile>());
    m.set_tile(Coord{5, 3}, std::make_shared<FireTile>());

    maps[m.get_id()] = m;

    shared_ptr<Human> a = std::make_shared<Human>(WorldCoord{m.get_id(), 0, 0});
    shared_ptr<Human> b = std::make_shared<Human>(WorldCoord{m.get_id(), 1, 1});

    entity_ps[a->get_id()] = a;
    entity_ps[b->get_id()] = b;

    move_entity(*a, WorldCoord{m.get_id(), 3, 4});

    a->interact(*b);
  }

  const Map& World::get_map(Identifiable::identifier_t id) const {
    return maps.at(id);
  }

  bool World::move_entity(Entity& entity, const WorldCoord& destination) {
    shared_ptr<Entity> entity_p = entity_ps.find(entity.get_id())->second;

    const WorldCoord prev_position = entity_p->get_position();

    if(entity_p->set_position(destination)) {
      maps[prev_position.map_id].get_tile(prev_position).exit(entity);
      maps[destination.map_id].get_tile(destination).enter(entity_p);
    }

    return true;
  }

  void World::tick() {
    for(pair<const Identifiable::identifier_t, shared_ptr<Entity>>& entity_pair : entity_ps) {
      entity_pair.second->tick();
    }

    for(pair<const Identifiable::identifier_t, Map>& map_pair : maps) {
      map_pair.second.tick();
    }
  }

}
