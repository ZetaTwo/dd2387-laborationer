#pragma once 

#include <vector>
#include <memory>

#include "entity.h"
#include "actors/goblin.h"
#include "game.h"

using std::vector;
using std::weak_ptr;
using std::shared_ptr;
using std::make_shared;

namespace lab3 {

  class GoblinQuest : public Entity {
  private:
    bool finished;
    vector<weak_ptr<PhysicalEntity>> goblins;
    GoblinBrain* brains_arr;

  public: 
    virtual inline string get_name() const override { return "Goblin Quest"; }
    virtual inline string get_description() const override  { return ""; }
    virtual void tick(Game& game) override;
    GoblinQuest(Game& game, Identifiable::identifier_t map_id);
    virtual ~GoblinQuest();
  };

}
