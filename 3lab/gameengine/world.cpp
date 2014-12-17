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

  void World::add_entity(shared_ptr<Entity> entity_p) {
    created_entities.push(entity_p);
  }
  void World::add_physical(shared_ptr<PhysicalEntity> physical_p) {
    add_entity(physical_p);
    created_physicals.push(physical_p);
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
    tick_entities(game);
    tick_tiles(game);
    remove_destroyed();
    add_created();
  }

  void World::tick_entities(Game& game) {
    //Perform input on all entities
    for (entities_t::value_type& entity_pair : entity_ps) {
      entity_pair.second->input(game);
    }

    //Perform tick on all entities
    for (entities_t::value_type& entity_pair : entity_ps) {
      entity_pair.second->tick(game);
    }
  }

  void World::tick_tiles(Game& game) {
    //Perform tick on all tiles
    for (maps_t::value_type& map_pair : maps) {
      map_pair.second.tick(game);
    }

    ++time;
  }

  void World::remove_destroyed() {
    //Destroy all waiting to be destroyed
    while (destroyed_entities.size() > 0) {
      entity_ps.erase(destroyed_entities.front());
      physical_ps.erase(destroyed_entities.front());
      destroyed_entities.pop();
    }
  }

  void World::add_created() {
    //Create all waiting to be created
    while (created_entities.size() > 0) {
      shared_ptr<Entity>& create = created_entities.front();
      entity_ps.emplace(entities_t::value_type{ create->get_id(), create });
      created_entities.pop();
    }
    while (created_physicals.size() > 0) {
      shared_ptr<PhysicalEntity>& create = created_physicals.front();
      physical_ps.emplace(physicals_t::value_type{ create->get_id(), create });
      created_physicals.pop();
    }
  }

}
