#pragma once
#include <memory>
#include <set>

#include "physicalentity.h"
#include "item.h"
#include "util.h"

using std::set;
using std::unique_ptr;

namespace lab3 {

  class Actor : public PhysicalEntity {
    protected:
      set<unique_ptr<CarriedItem>> inventory;
      bool is_remote_controlled = false;

      virtual void do_tick(Game& game);

    public:
      Actor(const WorldCoord& initial_position) : PhysicalEntity(initial_position) {};

      virtual bool move(Game& game, direction_t direction, unsigned int distance = 1) override;

      virtual bool add_item(Game& game, unique_ptr<CarriedItem>&& item_p);
      virtual bool drop_item(CarriedItem& item);
      virtual bool give_item(Game& game, unique_ptr<CarriedItem>&& item_p, Actor& recipient);
      virtual bool remove_item(CarriedItem& item);

      virtual bool set_remote_controlled(bool is_remote_controlled);
      virtual void interact(Actor& interactee);

      virtual void tick(Game& game) override final;
  };

}
