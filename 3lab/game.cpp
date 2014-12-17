#include<memory>

#include "actors/actor_basic.h"
#include "game.h"
#include "tiles/hazards.h"

using std::make_shared;
using std::move;

namespace lab3 {

  Game::Game() : Game(new Renderer(), new Inputer()) { }

  Game::Game(Renderer* renderer_p, Inputer* inputer_p) :
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

    inputer_p->evaluate_commands(*this);

    Entity& player = *get_player().get_actor();
    world.move_entity(*this, player, WorldCoord{world.get_maps().begin()->first, 3, 4});

    world.tick(*this);

    render();
  }

  void Game::run() {
    initialize();
    running = true;

    while(running) {
      get_input();
      tick();
    }
  }

  void Game::stop() {
    running = false;
  }

  void Game::get_input() const {
    inputer_p->get_input(*this);
  }

  void Game::render() const {
    renderer_p->render(*this);
  }

}
