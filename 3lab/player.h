#pragma once
#include <memory>

#include "actor.h"

using std::shared_ptr;

namespace lab3 {

  class Player : public ActorTicker {
      shared_ptr<Actor> actor;

      virtual void do_tick(Actor& tickee) const;

    public:
      Player(shared_ptr<Actor> actor);

      bool possess(Actor& new_actor);

      inline shared_ptr<Actor> get_actor() const { return actor; }
  };

}
