#pragma once
#include <functional>
#include <string>
#include <vector>

#include "actors/human.h"
#include "inputer.h"

using std::function;
using std::string;
using std::vector;

namespace lab3 {

  class OldMan : public Human {

    function<void(OldMan&, Game&)> ai_state_function;

    static function<void(OldMan&, Game&)> AI_STATE_WAIT_FOR_SHINY_THING;
    static function<void(OldMan&, Game&)> AI_STATE_GOBLINS_PANIC;
    static function<void(OldMan&, Game&)> AI_STATE_GO_TO_NORTH_WALL;

    bool has_shiny_thing() const;
    bool is_shiny_thing(const CarriedItem& item) const;

    virtual void do_tick(Game& game) override;

    public:
      OldMan(const WorldCoord& initial_position);
      OldMan(const WorldCoord& initial_position, const string& name);

      virtual void activated_by(Game& game, Actor& activator) override;
      virtual void activated_by(Game& game, Actor& activator, CarriedItem& item) override;

      virtual char to_char() const override { return 'M'; };
  };

}
