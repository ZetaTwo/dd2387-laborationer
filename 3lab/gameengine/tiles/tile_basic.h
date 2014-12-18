#pragma once

#include "tile.h"

namespace lab3 {
  class EmptyTile : public Tile {
    static const string description;

  public:
    virtual inline const string& get_description() const { return description; }
    virtual char to_char() const override { return ' '; };

  protected:
    virtual inline void do_stay(Game& game, PhysicalEntity&) override { }
    virtual inline void do_enter(Game& game, weak_ptr<PhysicalEntity>) override { }
    virtual inline void do_exit(Game& game, PhysicalEntity&) override { }
  };
}
