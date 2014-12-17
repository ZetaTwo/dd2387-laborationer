#pragma once

#include "tile.h"

namespace lab3 {
  class EmptyTile : public SingletonTile < EmptyTile > {
    static string description;

  public:
    virtual inline const string& get_description() const { return description; }

  protected:
    virtual inline void do_stay(Game& game, Entity&) override { }
    virtual inline void do_enter(Game& game, weak_ptr<Entity>) override { }
    virtual inline void do_exit(Game& game, Entity&) override { }
  };
}
