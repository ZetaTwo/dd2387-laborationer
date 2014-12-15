#pragma once
#include <iostream>
#include <memory>
#include <vector>

#include "tile.h"
#include "util.h"

using std::ostream;
using std::shared_ptr;
using std::vector;

namespace lab3 {

  class Tile;

  class Map : public virtual Identifiable {

    public:
      Map(vector<vector<shared_ptr<Tile>>> tiles);

      inline Coord top_left() const { return Coord{0, 0}; }
      Coord btm_right() const;
      inline CoordRectangle range() const { return CoordRectangle{top_left(), btm_right()}; }

      const Tile& get_tile(const Coord& coord) const;
      Tile& get_tile(const Coord& coord);

      bool set_tile                (const Coord& coord, shared_ptr<Tile> tile_p);
      bool insert_tile_north_of    (const Coord& coord, shared_ptr<Tile> tile_p);
      bool insert_tile_west_of     (const Coord& coord, shared_ptr<Tile> tile_p);
      bool push_back_tile_south_of (const Coord& coord, shared_ptr<Tile> tile_p);
      bool push_back_tile_east_of  (const Coord& coord, shared_ptr<Tile> tile_p);
      bool remove_tile_shift_north (const Coord& coord, shared_ptr<Tile> tile_p);
      bool remove_tile_shift_west  (const Coord& coord, shared_ptr<Tile> tile_p);

      void tick();
  };

  ostream& operator<<(ostream& os, const Map& map);

}
