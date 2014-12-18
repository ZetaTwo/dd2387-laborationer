#pragma once
#include <vector>
#include <list>
#include <memory>
#include <string>

using std::vector;
using std::list;
using std::shared_ptr;
using std::string;
using std::weak_ptr;

namespace lab3 {

  class Game;
  class PhysicalEntity;

  class Tile {
    protected:
      list<weak_ptr<PhysicalEntity>> entered_entities;

      void stay(Game& game, PhysicalEntity& stayer);
      virtual void do_stay(Game& game, PhysicalEntity& stayer) = 0;
      virtual void do_enter(Game& game, weak_ptr<PhysicalEntity> enterer_p) = 0;
      virtual void do_exit(Game& game, PhysicalEntity& exiter) = 0;

    public:
      void enter(Game& game, weak_ptr<PhysicalEntity> enterer_p);
      void exit(Game& game, PhysicalEntity& exiter);
      void tick(Game& game);

      virtual bool can_enter(PhysicalEntity& enterer) const;
      virtual char to_char() const = 0;

      virtual const string& get_description() const = 0;
      vector<shared_ptr<PhysicalEntity>> get_entities() const;
      shared_ptr<PhysicalEntity> get_entity() const;
  };
}
