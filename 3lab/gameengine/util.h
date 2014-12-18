#pragma once
#include <iostream>
#include <iterator>
#include <string>

using std::iterator;
using std::ostream;
using std::random_access_iterator_tag;
using std::string;

namespace lab3 {

  enum direction_t { DIR_NORTH, DIR_EAST, DIR_SOUTH, DIR_WEST };

  class Identifiable {
    public:
      typedef unsigned int identifier_t;

    private:
      const identifier_t id;
      Identifiable(const Identifiable&) = delete;
      Identifiable& operator=(const Identifiable&) = delete;

      static identifier_t next_id;
      inline static identifier_t get_new_identifier() { return next_id++; }

    protected:
      Identifiable() : id(get_new_identifier()) {}
      Identifiable(Identifiable&& other) : id(other.id) {}

    public:
      inline identifier_t get_id() const { return id; }
      inline bool operator==(const Identifiable& other) const { return id == other.id; }
      inline bool operator!=(const Identifiable& other) const { return !(*this == other); }

      virtual string get_name() const = 0;
      virtual string get_description() const = 0;
  };

  struct Coord {
    typedef size_t coord_t;
    coord_t x;
    coord_t y;

    Coord(const coord_t& x, const coord_t& y) : x(x), y(y) {}

    inline bool operator==(const Coord& rhs) const { return x == rhs.x && y == rhs.y; }
    inline bool operator!=(const Coord& rhs) const { return !(*this == rhs); }

    Coord step(direction_t direction, unsigned int distance = 1) const;
  };
  ostream& operator<<(ostream& os, const Coord& coord);

  struct WorldCoord : Coord {
    Identifiable::identifier_t map_id;

    WorldCoord(Identifiable::identifier_t map_id, coord_t x, coord_t y);
    WorldCoord(Identifiable::identifier_t map_id, const Coord& original);
    WorldCoord& operator=(const WorldCoord& other);

    inline bool operator==(const WorldCoord& rhs) const { return map_id == rhs.map_id && x == rhs.x && y == rhs.y; }
    inline bool operator!=(const WorldCoord& rhs) const { return !(*this == rhs); }

    WorldCoord step(direction_t direction, unsigned int distance = 1) const;
  };
  ostream& operator<<(ostream& os, const WorldCoord& coord);

  struct CoordRectangle {
      Coord top_left;
      Coord btm_right;

      class const_iterator;
      const_iterator begin() const;
      const_iterator end() const;

      inline bool operator==(const CoordRectangle& rhs) const {
        return top_left == rhs.top_left && btm_right == rhs.btm_right;
      }
      inline bool operator!=(const CoordRectangle& rhs) const { return !(*this == rhs); }
  };
  ostream& operator<<(ostream& os, const CoordRectangle& rect);

  class CoordRectangle::const_iterator : public iterator<random_access_iterator_tag, const Coord> {
    const CoordRectangle& rectangle;
    Coord current_coord;

    public:
      const_iterator(const CoordRectangle& rectangle);
      const_iterator(const CoordRectangle& rectangle, const Coord& begin_coord);
      const_iterator(const const_iterator& original);
      const_iterator& operator=(const const_iterator& original);

      const_iterator& operator++();
      const_iterator operator++(int);
      const_iterator& operator+=(difference_type);
      const_iterator operator+(difference_type) const;
      const_iterator& operator--();
      const_iterator operator--(int);
      const_iterator& operator-=(difference_type);
      const_iterator operator-(difference_type offset) const;
      difference_type operator-(const const_iterator& other) const;
      bool operator==(const const_iterator& rhs) const;
      bool operator!=(const const_iterator& rhs) const;
      bool operator<(const const_iterator& rhs) const;
      bool operator>(const const_iterator& rhs) const;
      bool operator>=(const const_iterator& rhs) const;
      bool operator<=(const const_iterator& rhs) const;
      const Coord& operator[](difference_type index) const;
      const Coord& operator*();
  };

}
