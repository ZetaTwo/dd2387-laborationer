#include <algorithm>

#include "map.h"

using std::endl;
using std::max_element;

namespace lab3 {

  Map::Map() :
    default_tile_p(EmptyTile::get_instance()) { }

  Map::Map(tile_ptr_t default_tile_p) :
    default_tile_p(default_tile_p) { }

  Map::Map(rows_t rows) :
    default_tile_p(EmptyTile::get_instance()),
    rows(rows) { }

  Map::Map(rows_t rows, tile_ptr_t default_tile_p) :
    default_tile_p(default_tile_p),
    rows(rows) { }

  Map& Map::operator=(const Map& other) {
    default_tile_p = other.default_tile_p;
    rows = other.rows;
    return *this;
  }

  Coord Map::btm_right() const {
    if(rows.size() == 0) {
      return Coord{0, 0};
    }

    auto max_x_row_it = max_element(rows.begin(), rows.end(),
      [](const row_t& a, const row_t& b) {
        return a.size() < b.size();
      }
    );

    return Coord{
      max_x_row_it == rows.end() ? 0 : max_x_row_it->size() == 0 ? 0 : max_x_row_it->size() - 1,
      rows.size() - 1
    };
  }

  Tile& Map::get_tile(const Coord& coord) {
    if(coord.y >= rows.size() || coord.x >= rows[coord.y].size()) {
      return *default_tile_p;
    }
    return *(rows[coord.y][coord.x]);
  }

  bool Map::set_tile(const Coord& coord, tile_ptr_t tile_p) {
    while(rows.size() <= coord.y) {
      rows.push_back(row_t{});
    }
    while(rows[coord.y].size() < coord.x) {
      rows[coord.y].push_back(default_tile_p);
    }

    if(rows[coord.y].size() == coord.x) {
      rows[coord.y].push_back(tile_p);
    } else {
      rows[coord.y][coord.x] = tile_p;
    }

    return true;
  }

  void Map::tick() {
    for(const Coord& coord : range()) {
      get_tile(coord).tick();
    }
  }

  ostream& operator<<(ostream& os, const Map& map) {
    size_t prev_row = 0;
    for(const Coord& xy : map.range()) {
      if(xy.y > prev_row) {
        prev_row = xy.y;
        os << endl;
      }
      os << xy << "\t";
    }

    return os;
  }

}
