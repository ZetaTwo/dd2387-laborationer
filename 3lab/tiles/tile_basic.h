#pragma once

#include "tile.h"

namespace lab3 {
  class EmptyTile : public SingletonTile < EmptyTile > {
    static string description;

  public:
    virtual inline void stay(Game& game, Entity&) override { }
    virtual inline void enter(Game& game, weak_ptr<Entity>) override { }
    virtual inline void exit(Game& game, Entity&) override { }

    virtual inline const string& get_description() const { return description; }
  };
}
