#pragma once
#include <string>
#include <vector>

#include "actors/human.h"
#include "inputer.h"

using std::string;
using std::vector;

namespace lab3 {

  class OldMan : public Human {

    public:
      OldMan(const WorldCoord& initial_position);
      OldMan(const WorldCoord& initial_position, const string& name);

      virtual void activated_by(Entity& activator) override;

      virtual char to_char() const override { return 'M'; };
  };

}
