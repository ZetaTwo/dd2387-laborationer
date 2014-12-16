#pragma once
#include <memory>
#include <set>

#include "entity.h"
#include "item.h"
#include "util.h"

using std::set;
using std::weak_ptr;

namespace lab3 {

  class Actor;
  class CarriedItem;

  class ActorTicker {
    public:
      virtual void do_tick(Actor& tickee) const = 0;
  };

  class Actor : public Entity, public ActorTicker {
    protected:
      set<CarriedItem> inventory;
      weak_ptr<ActorTicker> ticker_override_p;

      virtual void do_tick(Actor& tickee) const = 0;

    public:
      using Entity::Entity;

      virtual bool move(direction_t direction, unsigned int distance = 1) override;

      virtual bool add_item(CarriedItem& item);
      virtual bool drop_item(CarriedItem& item);
      virtual bool give_item(CarriedItem& item, Actor& recipient);
      virtual bool remove_item(CarriedItem& item);

      virtual bool override_ticker(ActorTicker& ticker_override);
      virtual void interact(Actor& interactee);

      virtual void tick() override;
  };

}
