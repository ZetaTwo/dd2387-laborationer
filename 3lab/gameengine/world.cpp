#include<memory>

#include "world.h"

using std::make_shared;
using std::move;
using std::pair;

namespace lab3 {

  class Map;

  World::World() {
  }

  const Map& World::get_map(Identifiable::identifier_t id) const {
    return maps.at(id);
  }

  bool World::add_map(Map&& map) {
    return maps.emplace(maps_t::value_type{map.get_id(), move(map)}).second;
  }

  bool World::add_entity(shared_ptr<Entity> entity_p) {
    return entity_ps.emplace(entities_t::value_type{entity_p->get_id(), entity_p}).second;
  }
  bool World::add_physical(shared_ptr<PhysicalEntity> physical_p) {
    if (add_entity(physical_p)) {
      return physical_ps.emplace(physicals_t::value_type{ physical_p->get_id(), physical_p }).second;
    }
    else {
      return false;
    }
  }

  bool World::move_entity(Game& game, PhysicalEntity& entity, const WorldCoord& destination) {
    //Find the entity
    shared_ptr<PhysicalEntity> entity_p = physical_ps.find(entity.get_id())->second;

    //Save previous position
    const WorldCoord prev_position = entity_p->get_position();
    if(prev_position == destination) {
      return false;
    }

    //Update position and trigger exit/enter hooks
    if(entity_p->set_position(destination)) {
      maps[prev_position.map_id].get_tile(prev_position).exit(game, entity);
      maps[destination.map_id].get_tile(destination).enter(game, entity_p);
    }

    return true;
  }

  void World::tick(Game& game) {
    //Perform input on all entities
    for (entities_t::value_type& entity_pair : entity_ps) {
      entity_pair.second->input(game);
    }

    //Perform tick on all entities
    for(entities_t::value_type& entity_pair : entity_ps) {
      entity_pair.second->tick(game);
    }

    //Perform tick on all tiles
    for(maps_t::value_type& map_pair : maps) {
      map_pair.second.tick(game);
    }
  }

}
