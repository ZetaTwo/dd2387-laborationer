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
    map<Identifiable::identifier_t, Map> maps;
    map<Identifiable::identifier_t, shared_ptr<Entity>> entity_ps;

    public:
      World();

      void tick();

      inline const map<Identifiable::identifier_t, Map>& get_maps() const { return maps; }
      const Map& get_map(Identifiable::identifier_t id) const;

      bool move_entity(Entity& entity, const WorldCoord& destination);
  };

}
