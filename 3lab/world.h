#pragma once
#include <list>
#include <map>

#include "entity.h"
#include "map.h"
#include "util.h"

using std::list;
using std::map;

namespace lab3 {

  class World {
    typedef map<Identifiable::identifier_t, Map> maps_t;
    typedef map<Identifiable::identifier_t, shared_ptr<Entity>> entities_t;
    maps_t maps;
    entities_t entity_ps;

    public:
      World();

      void tick();

      inline const maps_t& get_maps() const { return maps; }
      const Map& get_map(Identifiable::identifier_t id) const;
      bool add_map(Map&& map);

      inline const entities_t get_entities() const { return entity_ps; }

      bool add_entity(shared_ptr<Entity> entity_p);
      bool move_entity(Entity& entity, const WorldCoord& destination);
  };

}
