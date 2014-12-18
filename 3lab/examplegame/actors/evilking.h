#pragma once
#include <string>
#include <vector>

#include "actors/human.h"
#include "inputer.h"

using std::string;
using std::vector;

namespace lab3 {

  class EvilKing : public Human {

    protected:
      virtual void do_tick(Game& game) override;

    public:
      EvilKing(const WorldCoord& initial_position);
      EvilKing(const WorldCoord& initial_position, const string& name);

      virtual void activated_by(Entity& activator) override;

      virtual char to_char() const override { return 'K'; };
  };

}
