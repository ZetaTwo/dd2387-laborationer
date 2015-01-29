#include "game.h"
#include "item.h"

namespace lab3 {

  class Potion : public Item {
    public:
      Potion(const WorldCoord& position) : Item(position) {}

      virtual bool pick_up(Game& game, Actor& taker) override;

      virtual inline string get_name() const override { return "Shiny thing"; }
      virtual inline string get_description() const override { return "It's glinting faintly in the daylight, with a slight tint of red."; }

      virtual void tick(Game&) override { }
      virtual char to_char() const override { return '?'; };

      virtual bool is_solid()   const { return false; }
      virtual bool is_visible() const { return true; }
  };

  class CarriedPotion : public CarriedItem {
    public:
      virtual inline string get_name() const override { return "Enigmatic potion"; }
      virtual inline string get_description() const override { return "It's a glass vial containing a very viscous bright red liquid. It looks dangerous, but also strangely appetizing. How this survived the goblins' custody is a mystery."; }

      virtual inline void activate(Game& game, Actor& activator) override {
        game.push_message("It tastes awful, but you do feel slightly revitalized.");
        activator.damage(game, -100);
        activator.drop_item(*this);
      }
  };

}
