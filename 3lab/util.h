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
    int x;
    int y;
  };
  ostream& operator<<(ostream& os, const Coord& coord);

  struct WorldCoord : Coord {
    Identifiable::identifier_t map_id;
  };

}
