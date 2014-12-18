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

  class KingQuest : public Entity {
  private:
    weak_ptr<PhysicalEntity> king;


  public:
    virtual inline string get_name() const override { return "King Quest"; }
    virtual inline string get_description() const override  { return ""; }
    virtual void tick(Game& game) override;
    KingQuest(Game& game, Identifiable::identifier_t map_id);
  };

}