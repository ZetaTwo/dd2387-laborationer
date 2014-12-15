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

      const Tile& get_tile(const Coord& coord) const;
      Tile& get_tile(const Coord& coord);

      void tick();
  };

  ostream& operator<<(ostream& os, const Map& map);

}
