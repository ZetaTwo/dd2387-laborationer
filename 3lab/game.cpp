#include<memory>

#include "game.h"

using std::make_shared;
using std::move;

namespace lab3 {

  Game::Game() : Game(new Renderer(), new Inputer()) { }

  Game::Game(Renderer* renderer_p, Inputer* inputer_p) :
    renderer_p(renderer_p),
    inputer_p(inputer_p) {
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
