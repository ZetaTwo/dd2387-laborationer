#pragma once
#include <list>
#include <memory>
#include <string>

#include "entity.h"

using std::list;
using std::shared_ptr;
using std::string;
using std::weak_ptr;

namespace lab3 {

  class Entity;

  class Tile {
    protected:
      list<weak_ptr<Entity>> entered_entities;

      virtual void stay(Entity& stayer) = 0;

    public:
      virtual void enter(weak_ptr<Entity> enterer_p) = 0;
      virtual void exit(Entity& exiter) = 0;
      virtual void tick();

      virtual const string& get_description() const = 0;
  };

  template<class T>
  class SingletonTile : public Tile {
      static weak_ptr<T> the_instance;

    protected:
      using Tile::Tile;

    public:
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
  weak_ptr<T> SingletonTile<T>::the_instance;

  class EmptyTile : public SingletonTile<EmptyTile> {
      static string description;

    public:
      virtual inline void stay(Entity&) { }
      virtual inline void enter(weak_ptr<Entity>) { }
      virtual inline void exit(Entity&) { }

      virtual inline const string& get_description() const { return description; }
  };
}
