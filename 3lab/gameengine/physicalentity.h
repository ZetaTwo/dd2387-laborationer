#pragma once

#include "entity.h"
#include "util.h"

namespace lab3 {

  class Game;

  class PhysicalEntity : public Entity {
    protected:
      WorldCoord position;

    public:
      PhysicalEntity(const WorldCoord& initial_position);

      virtual bool is_solid()   const = 0;
      virtual bool is_visible() const = 0;

      inline const WorldCoord& get_position() const { return position; }
      bool set_position(const WorldCoord& pos);

      virtual bool move(direction_t direction, unsigned int distance = 1);

      virtual void activated_by(Entity& activator) = 0;
  };

}
