#pragma once
#include <string>
#include <vector>

#include "actors/human.h"
#include "inputer.h"

using std::string;
using std::vector;

namespace lab3 {

  class OldMan : public Human {

    bool has_shiny_thing() const;
    bool is_shiny_thing(const CarriedItem& item) const;

    public:
      OldMan(const WorldCoord& initial_position);
      OldMan(const WorldCoord& initial_position, const string& name);

      virtual void activated_by(Game& game, Actor& activator) override;
      virtual void activated_by(Game& game, Actor& activator, CarriedItem& item) override;

      virtual char to_char() const override { return 'M'; };
  };

}
