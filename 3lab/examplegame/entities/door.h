#pragma once

#include "physicalentity.h"

namespace lab3 {
  class Door : public PhysicalEntity {
    bool open;

  public:
    Door(const WorldCoord& initial_position) : PhysicalEntity(initial_position), open(false) {};

    virtual inline string get_name() const override { return "Door"; }
    virtual inline string get_description() const override  { return ""; }

    virtual void activated_by(Game& game, Actor& activator);

    virtual bool is_solid()   const override { return !open; }
    virtual bool is_visible() const override { return true; }
    virtual char to_char()    const override {
      return open ? 'L' : 'D';
    }

  };

}
