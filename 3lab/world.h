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
    list<shared_ptr<Entity>> entity_ps;

    public:
      void tick();

      const Map& get_map(Identifiable::identifier_t id) const;
  };

}
