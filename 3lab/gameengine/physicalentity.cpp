#include "physicalentity.h"

#include "map.h"
#include "game.h"
#include "tile.h"

using std::shared_ptr;
using std::vector;

namespace lab3 {

  PhysicalEntity::PhysicalEntity(const WorldCoord& initial_position) :
    position(initial_position) {}

  bool PhysicalEntity::move(Game&, direction_t, unsigned int) {
    return false;
  }

  bool PhysicalEntity::set_position(const WorldCoord& pos) {
    position = pos;
    return true;
  }

  shared_ptr<Tile> PhysicalEntity::get_adjacent_tile(Game& game, direction_t dir) const {
    const Map& map = game.get_world().get_map(get_position().map_id);
    const Coord& pos = get_position();

    return map.get_tile(pos.step(dir));
  }

  vector<shared_ptr<PhysicalEntity>> PhysicalEntity::get_adjacent_entities(Game& game, direction_t dir) const {
    const shared_ptr<Tile> tile = get_adjacent_tile(game, dir);
    return tile->get_entities();
  }

  shared_ptr<PhysicalEntity> PhysicalEntity::get_adjacent_entity(Game& game, direction_t dir) const {
    const shared_ptr<Tile> tile = get_adjacent_tile(game, dir);
    return tile->get_entity();
  }

}
