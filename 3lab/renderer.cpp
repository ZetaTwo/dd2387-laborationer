#include <iostream>

#include "renderer.h"

using std::cout;
using std::endl;

namespace lab3 {

  Renderer::Renderer(ostream& out) :
    out(out) {}

  void Renderer::render(const Game& game) {
    const Player& player = game.get_player();
    const Actor& player_actor = player.get_actor();

    const WorldCoord& player_position = player_actor.get_position();

    const Map& player_map = game.get_world().get_map(player_position.map_id);

    out << endl << endl << endl << endl << endl;

    out << "First map in world:" << endl;
    out << game.get_world().get_maps().begin()->second << endl;

    out << "Player map:" << endl;
    out << player_map << endl;
  };

}
