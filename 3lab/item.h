#pragma once
#include <string>

#include "actor.h"
#include "entity.h"

using std::string;

namespace lab3 {

  class Actor;

  class Item : public Entity {
    public:
      virtual bool pick_up(Actor& taker) = 0;
  };

  class CarriedItem : public Identifiable, public virtual Named {
    protected:
      int value;
      int volume;
      int weight;

    public:
      virtual int getValue() const;
      virtual int getVolume() const;
      virtual int getWeight() const;
      virtual void activate(Actor& activator);
  };

}
