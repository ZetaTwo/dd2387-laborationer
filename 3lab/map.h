#pragma once
#include <memory>
#include <vector>

#include "tile.h"
#include "util.h"

using std::shared_ptr;
using std::vector;

namespace lab3 {

  class Tile;

  class Map : public virtual Identifiable {

    public:
      Map(vector<vector<shared_ptr<Tile>>> tiles);

      const Tile& get_tile(const Coord& coord) const;
      const Tile& get_tile(int x, int y) const;
      Tile& get_tile(const Coord& coord);
      Tile& get_tile(int x, int y);

      void tick();
  };

}
