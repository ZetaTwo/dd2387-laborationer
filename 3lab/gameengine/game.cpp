#include "game.h"
#include "inputer.h"
#include "renderer.h"

namespace lab3 {

  Game::Game() : Game(new Renderer(), new Inputer()) { }

  Game::Game(Renderer* renderer_p, Inputer* inputer_p) :
    renderer_p(renderer_p),
    inputer_p(inputer_p) {
  }

  Game::~Game() {
    delete renderer_p;
    delete inputer_p;
  }

  void Game::push_message(const string& message) {
    messages.push_back(message);
  }

  void Game::clear_messages() {
    messages.clear();
  }

  void Game::tick() {
    clear_messages();
    world.tick(*this);
    render();
  }

  void Game::run() {
    initialize();
    running = true;

    while(running) {
      tick();
    }
  }

  void Game::stop() {
    running = false;
  }

  void Game::render() const {
    renderer_p->render(*this);
  }

}
