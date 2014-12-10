#pragma once
#include <list>
#include <memory>

#include "entity.h"

using std::list;
using std::weak_ptr;

namespace lab3 {

  class Entity;

  class Tile {
    protected:
      list<weak_ptr<Entity>> entered_entities;

      virtual void stay(Entity&);

    public:
      virtual void enter(weak_ptr<Entity> enterer_p);
      virtual void exit(Entity& exiter);
      virtual void tick();
  };

}
