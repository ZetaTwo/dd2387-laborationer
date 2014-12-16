#include<memory>

#include "actors/basic.h"
#include "game.h"

using std::make_shared;

namespace lab3 {

  shared_ptr<Game> Game::the_instance;

  Game::Game() : Game(make_shared<Renderer>(), make_shared<Inputer>()) { }

  Game::Game(shared_ptr<Renderer> renderer_p, shared_ptr<Inputer> inputer_p) :
    player(Player{make_shared<Human>(WorldCoord{world.get_maps().begin()->first, 0, 0}, "Ze Hero")}),
    renderer_p(renderer_p),
    inputer_p(inputer_p) {
      world.add_entity(player.get_actor());
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
