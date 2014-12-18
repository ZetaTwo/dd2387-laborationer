#pragma once
#include <memory>
#include <vector>

#include "entity.h"
#include "util.h"

using std::shared_ptr;
using std::vector;

namespace lab3 {

  class Game;
  class Tile;

  class PhysicalEntity : public Entity {
    protected:
      WorldCoord position;

    public:
      PhysicalEntity(const WorldCoord& initial_position);

      virtual bool is_solid()   const = 0;
      virtual bool is_visible() const = 0;
      virtual char to_char()    const = 0;

      inline const WorldCoord& get_position() const { return position; }
      bool set_position(const WorldCoord& pos);

      virtual bool move(direction_t direction, unsigned int distance = 1);

      virtual void activated_by(Entity& activator) = 0;

      vector<shared_ptr<PhysicalEntity>> get_adjacent_entities(Game& game, direction_t dir) const;
      shared_ptr<PhysicalEntity> get_adjacent_entity(Game& game, direction_t dir) const;
      shared_ptr<Tile> get_adjacent_tile(Game& game, direction_t dir) const;
  };

  class PhysicalEntityRenderOrderSorter {
  public:
    bool operator()(const shared_ptr<PhysicalEntity>& a, const shared_ptr<PhysicalEntity>& b) {
      if (a->is_visible() != b->is_visible()) {
        return a->is_visible();
      }
      
      if (a->is_solid() != b->is_solid()) {
        return a->is_solid();
      }

      return true;
    }
  };

}
