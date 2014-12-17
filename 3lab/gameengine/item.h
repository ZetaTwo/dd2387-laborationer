#pragma once
#include <string>

#include "entity.h"

namespace lab3 {

  class Actor;

  class Item : public Entity {
    public:
      virtual bool pick_up(Actor& taker) = 0;
  };

  class CarriedItem : public Identifiable {
    protected:
      int value;
      int volume;
      int weight;

    public:
      virtual inline int getValue() const { return value; }
      virtual inline int getVolume() const { return volume; }
      virtual inline int getWeight() const { return weight; }
      virtual inline void activate(Actor& activator) {}

      virtual inline std::string get_name() const override { return "CHANGEME"; }
      virtual inline std::string get_description() const override  { return "CHANGEME"; }
  };

}
