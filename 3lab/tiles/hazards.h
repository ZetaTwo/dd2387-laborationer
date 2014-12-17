#pragma once

#include "tile.h"

namespace lab3 {

  class FireTile : public Tile {
    int damage;

    static string description;

  protected:
    virtual void do_stay(Game& game, Entity&) override;
    virtual void do_enter(Game& game, weak_ptr<Entity>) override;
    virtual void do_exit(Game& game, Entity&) override;

  public:
      FireTile();
      FireTile(int damage);

      virtual inline const string& get_description() const { return description; }
  };
}
