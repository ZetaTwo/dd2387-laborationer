#pragma once

#include "util.h"

namespace lab3 {

  class Game;

  class Entity : public Identifiable {
    public:
      virtual void input(Game& game) {};
      virtual void tick(Game& game) = 0;
  };

}
