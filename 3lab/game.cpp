#include<memory>

#include "actors/basic.h"
#include "game.h"
#include "tiles/hazards.h"

using std::make_shared;
using std::move;

namespace lab3 {

  shared_ptr<Game> Game::the_instance;

  Game::Game() : Game(make_shared<Renderer>(), make_shared<Inputer>()) { }

  Game::Game(shared_ptr<Renderer> renderer_p, shared_ptr<Inputer> inputer_p) :
    renderer_p(renderer_p),
    inputer_p(inputer_p) {
  }

  void Game::initialize() {
    if(initialized) {
      throw std::runtime_error("Game has already been initialized!");
    }

    initialized = true;

    Map m;

    m.set_tile(Coord{3, 4}, std::make_shared<FireTile>());
    m.set_tile(Coord{2, 1}, std::make_shared<FireTile>());
    m.set_tile(Coord{5, 3}, std::make_shared<FireTile>());

    world.add_map(move(m));

    shared_ptr<Actor> player_actor_p = make_shared<Human>(WorldCoord{m.get_id(), 0, 0}, "Ze Hero");
    player.possess(player_actor_p);

    world.add_entity(player_actor_p);
    world.add_entity(make_shared<Human>(WorldCoord{m.get_id(), 0, 0}));
    world.add_entity(make_shared<Human>(WorldCoord{m.get_id(), 1, 1}));
  }

  void Game::push_message(const string& message) {
    messages.push_back(message);
  }

  void Game::clear_messages() {
    messages.clear();
  }

  void Game::tick() {
    clear_messages();

    Entity& player = *get_player().get_actor();
    world.move_entity(player, WorldCoord{world.get_maps().begin()->first, 3, 4});

    world.tick();

    renderer_p->render(*this);
  }

  void Game::run() {
    initialize();
    running = true;

    while(running) {
      tick();
      tick();
      tick();
      tick();
      stop();
    }
  }

  void Game::stop() {
    running = false;
  }

}
