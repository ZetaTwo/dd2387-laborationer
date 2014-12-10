#pragma once

#include "map.h"
#include "util.h"

namespace lab3 {

  class Entity : public Identifiable, public virtual Named {
    public:
      virtual bool is_solid()   const = 0;
      virtual bool is_visible() const = 0;

      WorldCoord get_position() const;
      const Map& get_map() const;

      virtual void activated_by(Entity& activator) = 0;
      virtual void tick() = 0;
  };

}
