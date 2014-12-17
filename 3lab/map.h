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
    protected:
      typedef shared_ptr<Tile> tile_ptr_t;
      typedef vector<tile_ptr_t> row_t;
      typedef vector<row_t> rows_t;

      tile_ptr_t default_tile_p;
      rows_t rows;

    public:
      Map();
      Map(tile_ptr_t default_tile);
      Map(const Map& original);
      Map(Map&& original);
      Map(rows_t rows);
      Map(rows_t rows, tile_ptr_t default_tile);
      Map& operator=(const Map& other);

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

      void tick(Game& game);

      virtual inline string get_name() const override { return "CHANGEME"; }
      virtual inline string get_description() const override  { return "CHANGEME"; }
  };

  ostream& operator<<(ostream& os, const Map& map);

}
