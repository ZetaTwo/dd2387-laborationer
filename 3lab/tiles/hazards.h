#pragma once

#include "tile.h"

namespace lab3 {

  class FireTile : public Tile {
      int damage;

      static string description;

  protected:
    virtual void stay(Game& game, Entity&) override;

  public:
      FireTile();
      FireTile(int damage);

      virtual void enter(Game& game, weak_ptr<Entity>) override;
      virtual void exit(Game& game, Entity&) override;
      

      virtual inline const string& get_description() const { return description; }
  };


}
