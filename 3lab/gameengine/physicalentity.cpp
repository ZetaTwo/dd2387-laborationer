#include "physicalentity.h"

namespace lab3 {

  PhysicalEntity::PhysicalEntity(const WorldCoord& initial_position) :
    position(initial_position) {}

  bool PhysicalEntity::move(direction_t, unsigned int) {
    return false;
  }

  bool PhysicalEntity::set_position(const WorldCoord& pos) {
    position = pos;
    return true;
  }

}
