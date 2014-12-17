#include<memory>

#include "actors/basic.h"
#include "tiles/hazards.h"
#include "world.h"

using std::make_shared;
using std::move;
using std::pair;

namespace lab3 {

  World::World() {
  }

  const Map& World::get_map(Identifiable::identifier_t id) const {
    return maps.at(id);
  }

  bool World::add_map(Map&& map) {
    return maps.emplace(pair<Identifiable::identifier_t, Map>(map.get_id(), move(map))).second;
  }

  bool World::add_entity(shared_ptr<Entity> entity_p) {
    if(entity_ps.count(entity_p->get_id()) > 0) {
      return false;
    }
    entity_ps[entity_p->get_id()] = entity_p;
    return true;
  }

  bool World::move_entity(Entity& entity, const WorldCoord& destination) {
    shared_ptr<Entity> entity_p = entity_ps.find(entity.get_id())->second;

    const WorldCoord prev_position = entity_p->get_position();
    if(prev_position == destination) {
      return false;
    }

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
