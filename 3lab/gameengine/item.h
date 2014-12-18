#pragma once
#include <string>
#include <utility>

#include "physicalentity.h"

using std::move;
using std::string;

namespace lab3 {

  class Actor;

  class Item : public PhysicalEntity {
    public:
      Item(const WorldCoord& position) : PhysicalEntity(position) {}
      virtual bool pick_up(Game& game, Actor& taker) = 0;
  };

  class CarriedItem : public Identifiable {
    protected:
      int value;
      int volume;
      int weight;

    public:
      CarriedItem() : value(0), volume(0), weight(0) {}

      virtual inline int getValue() const { return value; }
      virtual inline int getVolume() const { return volume; }
      virtual inline int getWeight() const { return weight; }
      virtual void activate(Game& game, Actor&);

      virtual inline string get_name() const override { return "CHANGEME"; }
      virtual inline string get_description() const override  { return "CHANGEME"; }
  };

}
