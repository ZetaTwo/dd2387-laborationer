#pragma once
#include <memory>

#include "util.h"
#include "actor.h"
#include "inputer.h"

using std::shared_ptr;
using std::string;

namespace lab3 {

  class Camera : public Entity {
    shared_ptr<PhysicalEntity> followee;
    public:
      explicit Camera() {};

      void set_followee(shared_ptr<PhysicalEntity> follow) {
        followee = follow;
      }

      virtual void tick(Game& game) override {};
      virtual string get_name() const override { return "Camera"; };
      virtual string get_description() const override { return ""; };
      inline const WorldCoord& get_position() const { return followee->get_position(); }
  };
}
