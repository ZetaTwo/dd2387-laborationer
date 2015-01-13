#pragma once
#include <string>
#include <vector>

#include "actors/human.h"
#include "inputer.h"

using std::string;
using std::vector;

namespace lab3 {

  class EvilKing : public Human {

      int hitpoints;

    protected:
      virtual void do_tick(Game& game) override;

    public:
      EvilKing(const WorldCoord& initial_position);
      EvilKing(const WorldCoord& initial_position, const string& name);

      virtual void activated_by(Game& game, Actor& activator) override;
      virtual void activated_by(Game& game, Actor& activator, CarriedItem& item) override;

      virtual char to_char() const override { return 'K'; };
  };

}
