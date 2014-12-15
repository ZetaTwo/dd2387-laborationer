#include "util.h"

namespace lab3 {

  Identifiable::identifier_t Identifiable::next_id = 0;

  ostream& operator<<(ostream& os, const Coord& coord) {
    return os << "(" << coord.x << ", " << coord.y << ")";
  }

  CoordRectangle::const_iterator CoordRectangle::begin() const {
    return const_iterator{*this};
  }

  CoordRectangle::const_iterator CoordRectangle::end() const {
    return const_iterator{*this, Coord{top_left.x, btm_right.y + 1}};
  }

  CoordRectangle::const_iterator::const_iterator(const CoordRectangle& rectangle) :
    rectangle(rectangle),
    current_coord(rectangle.top_left) {}

  CoordRectangle::const_iterator::const_iterator(const CoordRectangle& rectangle, const Coord& begin_coord) :
    rectangle(rectangle),
    current_coord(begin_coord) {}

  CoordRectangle::const_iterator::const_iterator(const const_iterator& original) :
    rectangle(original.rectangle),
    current_coord(original.current_coord) {}

  CoordRectangle::const_iterator& CoordRectangle::const_iterator::operator=(const const_iterator& original) {
    current_coord = original.current_coord;
    return *this;
  }

  CoordRectangle::const_iterator& CoordRectangle::const_iterator::operator++() {
    if(++current_coord.x > rectangle.btm_right.x) {
      current_coord.x = rectangle.top_left.x;
      ++current_coord.y;
    }
    return *this;
  }

  bool CoordRectangle::const_iterator::operator!=(const const_iterator& rhs) const {
    return rectangle != rhs.rectangle || current_coord != rhs.current_coord;
  }

  const Coord& CoordRectangle::const_iterator::operator*() {
    return current_coord;
  }

  ostream& operator<<(ostream& os, const CoordRectangle& rect) {
    return os << "CoordRectangle(" << rect.top_left << " - " << rect.btm_right << ")";
  }
}
