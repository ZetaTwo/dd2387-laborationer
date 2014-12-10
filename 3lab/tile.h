#pragma once
#include <list>
#include <memory>

#include "entity.h"

using std::list;
using std::shared_ptr;
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

  template<class T>
  class StatelessTile : public Tile {
    public:
      static weak_ptr<T> the_instance;
      static shared_ptr<T> get_instance() {
        if(the_instance.expired()) {
          shared_ptr<T> new_instance = std::make_shared<T>();
          the_instance = new_instance;
          return new_instance;
        }
        return the_instance.lock();
      }
  };
  template<class T>
  weak_ptr<T> StatelessTile<T>::the_instance;

}
