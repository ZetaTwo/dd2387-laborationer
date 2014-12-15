#pragma once
#include <iostream>
#include <string>

using std::ostream;
using std::string;

namespace lab3 {

  enum direction_t { DIR_NORTH, DIR_EAST, DIR_SOUTH, DIR_WEST };

  class Identifiable {
    public:
      typedef unsigned int identifier_t;

    private:
      const identifier_t id;
      Identifiable(const Identifiable&);
      Identifiable& operator=(const Identifiable&);

      static identifier_t next_id;
      inline static identifier_t get_new_identifier() { return next_id++; }

    public:
      Identifiable() : id(get_new_identifier()) {}
      Identifiable(Identifiable&& other) : id(other.id) {}
      inline identifier_t get_id() const { return id; }
      inline bool operator==(const Identifiable& other) { return id == other.id; }
  };

  class Named {
      string name;
      string description;

    public:
      Named(string name) : name(name), description("") {}
      Named(string name, string description) : name(name), description(description) {}
      inline const string& get_name() const { return name; }
      inline const string& get_description() const { return description; }
  };

  struct Coord {
    typedef size_t coord_t;
    coord_t x;
    coord_t y;

    inline bool operator==(const Coord& rhs) const { return x == rhs.x && y == rhs.y; }
    inline bool operator!=(const Coord& rhs) const { return !(*this == rhs); }
  };
  ostream& operator<<(ostream& os, const Coord& coord);

  struct WorldCoord : Coord {
    Identifiable::identifier_t map_id;
  };

  struct CoordRectangle {
      Coord top_left;
      Coord btm_right;

      inline bool operator==(const CoordRectangle& rhs) const {
        return top_left == rhs.top_left && btm_right == rhs.btm_right;
      }
      inline bool operator!=(const CoordRectangle& rhs) const { return !(*this == rhs); }
  };
  ostream& operator<<(ostream& os, const CoordRectangle& rect);

}
