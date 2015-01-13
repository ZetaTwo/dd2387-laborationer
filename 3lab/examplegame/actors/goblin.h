#pragma once
#include <string>
#include <vector>

#include "actor.h"
#include "inputer.h"

using std::string;
using std::vector;

namespace lab3 {

  class Goblin : public Actor {
    protected:
      virtual void do_tick(Game& game) override;

    public:
      Goblin(const WorldCoord& initial_position);
      Goblin(const WorldCoord& initial_position, const string& name);

      virtual inline bool is_solid() const { return true; }
      virtual inline bool is_visible() const { return true; }

      virtual void activated_by(Game& game, Actor& activator) override;
      virtual void activated_by(Game& game, Actor& activator, CarriedItem& item) override;

      virtual char to_char() const override { return 'G'; };
      virtual inline string get_name() const override { return "Goblin"; }
      virtual inline string get_description() const override  { return ""; }
  };

}
