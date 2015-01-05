#pragma once

#include "tile.h"

namespace lab3 {

  class RockTile : public Tile {
    static const string description;

  protected:
    virtual inline void do_stay(Game&, PhysicalEntity&) override {}
    virtual inline void do_enter(Game&, weak_ptr<PhysicalEntity>) override {}
    virtual inline void do_exit(Game&, PhysicalEntity&) override {}

  public:
      RockTile() {};

      virtual inline bool can_enter(PhysicalEntity&) const { return false; }
      virtual inline char to_char() const override { return '#'; }

      virtual inline const string& get_description() const { return description; }
  };
}
