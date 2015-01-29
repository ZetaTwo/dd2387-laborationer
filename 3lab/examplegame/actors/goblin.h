#pragma once
#include <string>
#include <vector>

#include "actor.h"
#include "inputer.h"

using std::string;
using std::vector;

namespace lab3 {

  struct GoblinBrain;

  class Goblin : public Actor {
      friend struct GoblinBrain;
      friend class GoblinQuest;

    protected:
      GoblinBrain* brain_p;

      virtual void do_tick(Game& game) override;

      static const int ATTACK_DAMAGE = 3;

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

      void set_brain(GoblinBrain* brain_p);
  };

  struct GoblinBrain {
      std::function<void(Goblin& goblin, Game& game)> do_tick;
      std::function<void(Goblin& goblin, Game& game, Actor& activator)> activated_by;
      std::function<void(Goblin& goblin, Game& game, Actor& activator, CarriedItem& item)> activated_with_item;
  };

}
