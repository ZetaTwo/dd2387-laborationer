#include <iostream>
#include <memory>
#include <vector>

#include "game.h"
#include "map.h"
#include "tile.h"
#include "renderer.h"

using namespace lab3;
using std::vector;

using std::cout;
using std::endl;

void Tile::tick() {
  cout << "tick" << endl;

  entered_entities.remove_if([](weak_ptr<Entity> entity_p) {
    return entity_p.expired();
  });

  for(const weak_ptr<Entity> entity_p : entered_entities) {
    stay(*(entity_p.lock()));
  }
}

void Tile::enter(const weak_ptr<Entity> enterer_p) {
  entered_entities.push_back(enterer_p);
  cout << "enter" << endl;
}

void Tile::exit(Entity& exiter) {
  entered_entities.remove_if([&exiter](weak_ptr<Entity> entity_p) {
    return entity_p.expired() || (*(entity_p.lock()) == exiter);
  });
  cout << "exit" << endl;
}
void Tile::stay(Entity&) { cout << "stay" << endl; }

    //StatelessTile() { cout << "StatelessTile()" << endl; }

    //~StatelessTile() { cout << "~StatelessTile()" << endl; }

class FireTile : public StatelessTile<FireTile> {
  public:
    FireTile() { cout << "FireTile constructor" << endl; }
    ~FireTile() { cout << "FireTile destructor" << endl; }

    void enter(weak_ptr<Entity> enterer_p) {
      Tile::enter(enterer_p);
      if(!enterer_p.expired()) {
        cout << enterer_p.lock()->get_name() << " is on fire!" << endl;
      }
    }

    void exit(Entity& exiter) {
      Tile::exit(exiter);
      cout << exiter.get_name() << " isn't on fire anymore!" << endl;
    }

    void stay(Entity& stayer) {
      Tile::stay(stayer);
      cout << stayer.get_name() << " is still on fire!" << endl;
    }
};

class Foo : public Entity {
  public:
    Foo() : Named("Foo") { cout << "Construct Foo " << get_id() << endl; }
    ~Foo() { cout << "Destroy Foo " << get_id() << endl; }
    virtual inline bool is_solid() const override { return false; }
    virtual inline bool is_visible() const override { return true; }
    virtual inline void activated_by(Entity&) override {}
    virtual inline void tick() override {}
};

struct I : public virtual Identifiable {
  int i;
  I() : Identifiable(), i(0) {}
  explicit I(int i) : Identifiable(), i(i) {}
  I(const I& original) : Identifiable(), i(original.i) {}
  I& operator=(const I& other) { i = other.i; return *this; }
};

void Game::run() {
  cout << "Run game" << endl;
}

I make_I(int i = 0) {
  I the_i(i);
  cout << "Made i: " << the_i.get_id() << " " << the_i.i << endl;
  return the_i;
}

bool Entity::move(direction_t, unsigned int) { return false; }

void Player::do_tick(Actor&) const {}
void Actor::do_tick(Actor&) const {}

bool Actor::add_item(CarriedItem&) { return false; }
bool Actor::drop_item(CarriedItem&) { return false; }
bool Actor::give_item(CarriedItem&, Actor&) { return false; }
bool Actor::remove_item(CarriedItem&) { return false; }
bool Actor::override_ticker(ActorTicker&) { return false; }
void Actor::interact(Actor&) {}

int CarriedItem::getValue() const { return 0; }
int CarriedItem::getVolume() const { return 0; }
int CarriedItem::getWeight() const { return 0; }
void CarriedItem::activate(Actor&) { }

class GreetingActor : public Actor {
  public:
    GreetingActor(string name) : Named(name) {}
    virtual void interact(Actor& interactee) override {
      cout << "Greetings, " << interactee.get_name() << "!" << endl;
      interactee.activated_by(*this);
    }
    virtual void activated_by(Entity& activator) override {
      cout << "Hello, " << activator.get_name() << "!" << endl;
    }

    inline virtual bool is_solid() const override { return true; }
    inline virtual bool is_visible() const override { return true; }
    inline virtual void tick() override {}
};


int main() {
  Game g;
  g.run();

  shared_ptr<GreetingActor> a = std::make_shared<GreetingActor>("Bert");
  GreetingActor b("Eva");

  a->interact(b);

  vector<vector<std::shared_ptr<Tile>>> tiles{10, vector<std::shared_ptr<Tile>>{10}};
  tiles[0][0] = FireTile::get_instance();
  tiles[0][1] = FireTile::get_instance();
  tiles[0][2] = FireTile::get_instance();

  shared_ptr<Entity> f = std::make_shared<Foo>();

  tiles[0][0]->enter(a);

  tiles[0][0]->tick();
  tiles[0][0]->tick();

  tiles[0][0]->exit(*a);

  tiles[0][0]->tick();
  tiles[0][0]->tick();

  I i(5);
  I j{i};
  I k = make_I(42);
  cout << i.get_id() << " " << i.i << " " << endl;
  cout << j.get_id() << " " << j.i << " " << endl;
  cout << k.get_id() << " " << k.i << " " << endl;
  k = make_I(1337);
  cout << k.get_id() << " " << k.i << " " << endl;

  cout << endl << (i == i) << " " << (i == j) << endl;

  Map m{
    {
      { FireTile::get_instance(), FireTile::get_instance(), FireTile::get_instance() },
      { FireTile::get_instance(), FireTile::get_instance(), FireTile::get_instance() },
      { FireTile::get_instance(), FireTile::get_instance(), FireTile::get_instance() }
    }
  };

  cout << m.range() << endl;

  cout << m.top_left() << endl;
  cout << m.btm_right() << endl;

  cout << *(m.range().begin()) << endl;
  cout << *(m.range().end()) << endl;

  cout << (Coord{0, 0} == Coord{0, 0}) << endl;
  cout << (Coord{0, 0} == Coord{1, 0}) << endl;
  cout << (Coord{0, 0} != Coord{0, 0}) << endl;
  cout << (Coord{0, 0} != Coord{1, 0}) << endl;

  cout << m << endl;
}
