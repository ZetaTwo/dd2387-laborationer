#include <algorithm>

#include "map.h"
#include "tiles/tile_basic.h"

using std::endl;
using std::max_element;
using std::move;
using std::make_shared;

namespace lab3 {

  Map::Map() { }

  Map::Map(rows_t rows) :
    rows(rows) { }

  Map::Map(Map&& original) : Identifiable(move(original)),
    rows(move(original.rows)) { }

  Map& Map::operator=(const Map& other) {
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

  const shared_ptr<Tile> Map::get_tile(const Coord& coord) const {
    if(coord.y >= rows.size() || coord.x >= rows[coord.y].size()) {
      return make_shared<EmptyTile>();
    }
    return (rows[coord.y][coord.x]);
  }

  shared_ptr<Tile> Map::get_tile(const Coord& coord) {
    if (coord.y >= rows.size() || coord.x >= rows[coord.y].size()) {
      return make_shared<EmptyTile>();
    }
    return (rows[coord.y][coord.x]);
  }

  bool Map::set_tile(const Coord& coord, tile_ptr_t tile_p) {
    while(rows.size() <= coord.y) {
      rows.push_back(row_t{});
    }
    while(rows[coord.y].size() < coord.x) {
      rows[coord.y].push_back(make_shared<EmptyTile>());
    }

    if(rows[coord.y].size() == coord.x) {
      rows[coord.y].push_back(tile_p);
    } else {
      rows[coord.y][coord.x] = tile_p;
    }

    return true;
  }

  void Map::tick(Game& game) {
    for(const Coord& coord : range()) {
      get_tile(coord)->tick(game);
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
