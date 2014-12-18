#pragma once
#include <string>
#include <vector>

#include "actor.h"
#include "inputer.h"

using std::string;
using std::vector;

namespace lab3 {

  class OldMan : public Actor {

    protected:
      virtual void do_tick(Game& game) override;

    public:
      OldMan(const WorldCoord& initial_position);
      OldMan(const WorldCoord& initial_position, const string& name);

      virtual inline bool is_solid() const { return true; }
      virtual inline bool is_visible() const { return true; }

      virtual void activated_by(Entity& activator) override;

      virtual char to_char() const override { return 'M'; };
      virtual inline string get_name() const override { return "Old Man"; }
      virtual inline string get_description() const override  { return ""; }
  };

}
