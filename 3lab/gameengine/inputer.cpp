#include "game.h"
#include "inputer.h"

namespace lab3 {

  void Inputer::render_game(const Game& game) const {
    game.render();
  }

}
