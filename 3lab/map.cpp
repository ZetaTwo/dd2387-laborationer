#include <algorithm>

#include "map.h"

using std::endl;
using std::max_element;

namespace lab3 {

  Map::Map(rows_t rows) :
    rows(rows) { }

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
