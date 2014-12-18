#pragma once
#include <string>
#include <vector>

#include "actor.h"
#include "inputer.h"

using std::string;
using std::vector;

namespace lab3 {

  class EvilKing : public Actor {

    protected:
      virtual void do_tick(Game& game) override;

    public:
      EvilKing(const WorldCoord& initial_position);
      EvilKing(const WorldCoord& initial_position, const string& name);

      virtual inline bool is_solid() const { return true; }
      virtual inline bool is_visible() const { return true; }

      virtual void activated_by(Entity& activator) override;

      virtual char to_char() const override { return 'K'; };
      virtual inline string get_name() const override { return "Evil King"; }
      virtual inline string get_description() const override  { return ""; }
  };

}
