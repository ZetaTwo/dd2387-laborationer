#include "item.h"

namespace lab3 {

  class QuestItem : public Item {
    public:
      QuestItem(const WorldCoord& position) : Item(position) {}

      virtual bool pick_up(Game& game, Actor& taker) override;

      virtual inline string get_name() const override { return "Something shiny"; }
      virtual inline string get_description() const override { return "Shiiiiiinyyyyy!"; }

      virtual void tick(Game&) override { }
      virtual char to_char() const override { return 'S'; };

      virtual bool is_solid()   const { return true; }
      virtual bool is_visible() const { return true; }
  };

  class QuestCarriedItem : public CarriedItem {
    public:
      virtual inline string get_name() const override { return "Shiny bauble"; }
      virtual inline string get_description() const override  { return "It's shiny! Someone is probably missing this."; }
  };

}
