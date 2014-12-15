#pragma once
#include <memory>

#include "actor.h"

using std::shared_ptr;

namespace lab3 {

  class Player : public ActorTicker {
      shared_ptr<Actor> actor;

      virtual void do_tick(Actor& tickee) const;

    public:
      bool possess(Actor& new_actor);
  };

}