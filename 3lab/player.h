#pragma once
#include <memory>

#include "actor.h"
#include "inputer.h"

using std::shared_ptr;

namespace lab3 {

  class Player {
      shared_ptr<Actor> actor;

    public:
      bool possess(const shared_ptr<Actor>& new_actor);
      void tick(Inputer& inputer) const;

      inline shared_ptr<Actor> get_actor() const { return actor; }
  };
}
