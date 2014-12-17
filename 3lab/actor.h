#pragma once
#include <memory>
#include <set>

#include "entity.h"
#include "item.h"
#include "util.h"

namespace lab3 {

  class Actor : public Entity {
    protected:
      std::set<CarriedItem> inventory;
      bool is_remote_controlled = false;

      virtual void do_tick(Game& game);

    public:
      Actor(const WorldCoord& initial_position) : Entity(initial_position) {};

      virtual bool move(direction_t direction, unsigned int distance = 1) override;

      virtual bool add_item(CarriedItem& item);
      virtual bool drop_item(CarriedItem& item);
      virtual bool give_item(CarriedItem& item, Actor& recipient);
      virtual bool remove_item(CarriedItem& item);

      virtual bool set_remote_controlled(bool is_remote_controlled);
      virtual void interact(Actor& interactee);

      virtual void tick(Game& game) override final;
  };

}
