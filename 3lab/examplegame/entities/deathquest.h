#pragma once

#include <memory>

#include "actor.h"
#include "entity.h"
#include "game.h"

using std::weak_ptr;

namespace lab3 {

  class DeathQuest : public Entity {
  private:
    weak_ptr<Actor> hero_p;

  public:
    DeathQuest(const shared_ptr<Actor> hero_p) : hero_p(hero_p) {}

    virtual inline string get_name() const override { return "Death Quest"; }
    virtual inline string get_description() const override  { return "If you die, you lose."; }
    virtual void tick(Game& game) override;
  };

}
