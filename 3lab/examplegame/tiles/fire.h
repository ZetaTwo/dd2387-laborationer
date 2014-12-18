#pragma once

#include "tile.h"

namespace lab3 {

  class FireTile : public Tile {
    int damage;

    static string description;

  protected:
    virtual void do_stay(Game& game, PhysicalEntity&) override;
    virtual void do_enter(Game& game, weak_ptr<PhysicalEntity>) override;
    virtual void do_exit(Game& game, PhysicalEntity&) override;

  public:
      FireTile();
      FireTile(int damage);

      virtual char to_char() const override { return 'F'; };
      virtual inline const string& get_description() const { return description; }
  };
}
