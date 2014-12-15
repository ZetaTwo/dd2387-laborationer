#include "util.h"

namespace lab3 {

  Identifiable::identifier_t Identifiable::next_id = 0;

  ostream& operator<<(ostream& os, const Coord& coord) {
    return os << "(" << coord.x << ", " << coord.y << ")";
  }

  ostream& operator<<(ostream& os, const CoordRectangle& rect) {
    return os << "CoordRectangle(" << rect.top_left << " - " << rect.btm_right << ")";
  }
}
