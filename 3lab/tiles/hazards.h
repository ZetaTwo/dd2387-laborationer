#pragma once

#include "tile.h"

namespace lab3 {

  class FireTile : public Tile {
      int damage;

      static string description;

    public:
      FireTile();
      FireTile(int damage);

      virtual void enter(weak_ptr<Entity>) override;
      virtual void exit(Entity&) override;
      virtual void stay(Entity&) override;

      virtual inline const string& get_description() const { return description; }
  };


}
