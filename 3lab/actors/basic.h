#pragma once
#include <string>

#include "actor.h"
#include "entity.h"

using std::string;

namespace lab3 {

  class Human : public Actor {
  private:
    string name;

    protected:
      virtual void do_tick(Actor& tickee) const override;

    public:
      Human(const WorldCoord& initial_position);
      Human(const WorldCoord& initial_position, const string& name);

      virtual inline bool is_solid() const { return true; }
      virtual inline bool is_visible() const { return true; }

      virtual void activated_by(Entity& activator) override;

      static const vector<string> FIRST_NAMES;
      static const vector<string> LAST_NAMES;

      static string new_name();
      virtual inline string get_name() const override { return name; }
      virtual inline string get_description() const override  { return ""; }
  };

}
