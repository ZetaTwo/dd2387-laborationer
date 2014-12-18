#pragma once
#include <list>
#include <map>
#include <queue>

#include "physicalentity.h"
#include "map.h"
#include "util.h"

using std::shared_ptr;
using std::map;
using std::queue;

namespace lab3 {

  class World {
    public:
      typedef map<Identifiable::identifier_t, Map> maps_t;
      typedef map<Identifiable::identifier_t, shared_ptr<PhysicalEntity>> physicals_t;
      typedef map<Identifiable::identifier_t, shared_ptr<Entity>> entities_t;
      typedef unsigned int time_t;

    private:
      maps_t maps;
      entities_t entity_ps;
      physicals_t physical_ps;
      time_t time = 0;
      queue<shared_ptr<Entity>> created_entities;
      queue<shared_ptr<PhysicalEntity>> created_physicals;
      queue<Identifiable::identifier_t> destroyed_entities;

      void tick_entities(Game& game);
      void tick_tiles(Game& game);
      void remove_destroyed();
      void add_created(Game& game);

    public:
      World();

      void tick(Game& game);
      inline time_t get_time() const { return time; }

      inline const maps_t& get_maps() const { return maps; }
      const Map& get_map(Identifiable::identifier_t id) const;
      bool add_map(Map&& map);

      inline const entities_t get_entities() const { return entity_ps; }
      inline const physicals_t get_physicals() const { return physical_ps; }

      void add_entity(shared_ptr<Entity> entity_p);
      void add_physical(shared_ptr<PhysicalEntity> physical_p);
      bool move_entity(Game& game, PhysicalEntity& entity, const WorldCoord& destination);
  };

}
