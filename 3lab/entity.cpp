#include "entity.h"

namespace lab3 {

  Entity::Entity(const WorldCoord& initial_position) :
    position(initial_position) {}

  bool Entity::move(direction_t, unsigned int) {
    return false;
  }

  bool Entity::set_position(const WorldCoord& pos) {
    position = pos;
    return true;
  }

}
