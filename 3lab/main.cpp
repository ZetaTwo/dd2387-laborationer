#include "game.h"

using namespace lab3;

int main() {
  Game& g = *Game::get_instance();
  g.run();
}
